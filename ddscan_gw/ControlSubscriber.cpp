#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include "ControlCommand.h"
#include "ControlCommandPubSubTypes.h"
#include <thread>
#include <chrono>
#include <signal.h>
#include "s32g3_skku_can_setting.h"

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;

std::atomic<bool> running(true);

int32_t steering_data, leftspeed_data, rightspeed_data;
unsigned char can_msg_steering[4];
unsigned char can_msg_speed[8];

void sendShutdownMessages()
{
    // Speed message (0x123) - 모든 값을 0으로
    memset(can_msg_speed, 0, 8);
    send_can_msg(0x123, can_msg_speed, 8);

    // Steering message (0x111) - [0,0,0,7]
    can_msg_steering[0] = 0;
    can_msg_steering[1] = 0;
    can_msg_steering[2] = 0;
    can_msg_steering[3] = 7;
    send_can_msg(0x111, can_msg_steering, 4);
    
    std::cout << "Shutdown messages sent" << std::endl;
}

void signalHandler(int signum)
{
    if (signum == SIGTERM || signum == SIGINT)
    {
        running = false;
    }
}


class ControlListener : public DataReaderListener {
public:
    ControlListener() : matched_(0) {
        std::cout << "ControlListener created" << std::endl;
    }

    void on_subscription_matched(DataReader*, const SubscriptionMatchedStatus& info) override {
        if (info.current_count_change > 0) {
            matched_++;
            std::cout << "Publisher matched! Total matches: " << matched_ << std::endl;
        } else {
            matched_--;
            std::cout << "Publisher unmatched! Total matches: " << matched_ << std::endl;
            sendShutdownMessages();
        }
    }

    void on_data_available(DataReader* reader) override {
        interfaces_pkg::msg::dds_::MotionCommand_ sample;
        SampleInfo info;
        
        while (reader->take_next_sample(&sample, &info) == ReturnCode_t::RETCODE_OK) {
            if (info.valid_data) {
                //std::cout << "Received Control Command:" << std::endl;
                //std::cout << "  Steering: " << sample.steering() << std::endl;
                //std::cout << "  Left Speed: " << sample.left_speed() << std::endl;
                //std::cout << "  Right Speed: " << sample.right_speed() << std::endl;

                // Steering CAN message
                steering_data = sample.steering();
                can_msg_steering[0] = 0;
                can_msg_steering[1] = 0;
                can_msg_steering[2] = 0;
                can_msg_steering[3] = (steering_data + 7) & 0xFF;

                // Speed CAN message
                leftspeed_data = sample.left_speed();
                rightspeed_data = sample.right_speed();
                // Left speed 데이터 (상위 4바이트)
                can_msg_speed[0] = (leftspeed_data < 0) ? 1 : 0;
                can_msg_speed[1] = 0;
                can_msg_speed[2] = 0;
                can_msg_speed[3] = (leftspeed_data < 0) ? -leftspeed_data : leftspeed_data;
                // Right speed 데이터 (하위 4바이트)
                can_msg_speed[4] = (rightspeed_data < 0) ? 1 : 0;
                can_msg_speed[5] = 0;
                can_msg_speed[6] = 0;
                can_msg_speed[7] = (rightspeed_data < 0) ? -rightspeed_data : rightspeed_data;

                // CAN 메시지 전송
                send_can_msg(0x111, can_msg_steering, 4);
                send_can_msg(0x123, can_msg_speed, 8);

            }
        }
    }

private:
    int matched_;
};

int main(int argc, char** argv) {
    // CAN 초기화
    can_setting();

    // Signal Handler 등록
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    // Create participant with default QoS
    DomainParticipantQos participant_qos = PARTICIPANT_QOS_DEFAULT;
    
    // ROS2와 동일한 QoS 설정을 위한 Reliability 설정
    participant_qos.wire_protocol().builtin.discovery_config.discoveryProtocol = 
        eprosima::fastrtps::rtps::DiscoveryProtocol_t::SIMPLE;
    participant_qos.wire_protocol().builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol = true;
    participant_qos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationReaderANDSubscriptionWriter = true;
    participant_qos.wire_protocol().builtin.discovery_config.m_simpleEDP.use_PublicationWriterANDSubscriptionReader = true;

    auto participant = DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);
    if (participant == nullptr) {
        std::cerr << "Create participant failed" << std::endl;
        return 1;
    }

    // Register the Type
    TypeSupport type(new interfaces_pkg::msg::dds_::MotionCommand_PubSubType());
    type.register_type(participant);

    // Create Subscriber with default QoS
    auto subscriber = participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT);
    if (subscriber == nullptr) {
        std::cerr << "Create subscriber failed" << std::endl;
        return 1;
    }

    // Create Topic with default QoS
    auto topic = participant->create_topic(
        "rt/topic_control_signal",
        type.get_type_name(),
        TOPIC_QOS_DEFAULT);
    
    if (topic == nullptr) {
        std::cerr << "Create topic failed" << std::endl;
        return 1;
    }

    // DataReader QoS 설정
    DataReaderQos reader_qos = DATAREADER_QOS_DEFAULT;
    reader_qos.reliability().kind = RELIABLE_RELIABILITY_QOS;  // ROS2와 동일한 Reliability 설정
    
    // Create DataReader with modified QoS
    auto listener = new ControlListener();
    auto reader = subscriber->create_datareader(
        topic,
        reader_qos,
        listener);

    if (reader == nullptr) {
        std::cerr << "Create datareader failed" << std::endl;
        return 1;
    }

    std::cout << "FastDDS Control Subscriber started on domain 0." << std::endl;

    // Block the current thread until SIGINT
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 종료 시 초기화 메시지 전송
    sendShutdownMessages();

    // Clean up
    if (reader != nullptr)
        subscriber->delete_datareader(reader);
    if (topic != nullptr)
        participant->delete_topic(topic);
    if (subscriber != nullptr)
        participant->delete_subscriber(subscriber);
    if (participant != nullptr)
        DomainParticipantFactory::get_instance()->delete_participant(participant);
    
    delete listener;

    std::cout << "Program terminated safely." << std::endl;
    return 0;
}