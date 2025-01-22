#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/core/policy/QosPolicies.hpp>
#include "Image.h"
#include "ImagePubSubTypes.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <cstdint>
#include <signal.h>
#include <atomic>

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;

std::atomic<bool> running(true);

void signalHandler(int signum)
{
    if (signum == SIGTERM || signum == SIGINT) {
        running = false;
    }
}


class ImageListener : public DataWriterListener {
public:
    ImageListener() : matched_(0) {}

    void on_publication_matched(DataWriter*, const PublicationMatchedStatus& info) override {
        if (info.current_count_change > 0) {
            matched_++;
            std::cout << "Subscriber matched! Total matches: " << matched_ << std::endl;
        } else {
            matched_--;
            std::cout << "Subscriber unmatched! Total matches: " << matched_ << std::endl;
        }
    }

private:
    int matched_;
};

class CameraServer {
private:
    // UDP 관련 변수
    int sock;
    struct sockaddr_in addr;
    
    // FastDDS 관련 변수
    DomainParticipant* participant_;
    Publisher* publisher_;
    Topic* topic_;
    DataWriter* writer_;
    TypeSupport type_;
    sensor_msgs::msg::dds_::Image_ image_data_;
    
    bool running_;
    std::thread receive_thread_;

    void setupUDP(int port) {
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            throw std::runtime_error("Socket creation failed");
        }

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            throw std::runtime_error("Bind failed");
        }
    }

    void setupDDS() {
        // Create participant
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
        if (participant_ == nullptr) {
            throw std::runtime_error("Create participant failed");
        }

        // Register type
        type_ = TypeSupport(new sensor_msgs::msg::dds_::Image_PubSubType());
        type_.register_type(participant_);

        // Create publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT);
        if (publisher_ == nullptr) {
            throw std::runtime_error("Create publisher failed");
        }

        // Create topic
        topic_ = participant_->create_topic(
            "rt/image_raw",
            type_.get_type_name(),
            TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr) {
            throw std::runtime_error("Create topic failed");
        }

        // Create DataWriter
        writer_ = publisher_->create_datawriter(
            topic_,
            DATAWRITER_QOS_DEFAULT,
            new ImageListener());
        if (writer_ == nullptr) {
            throw std::runtime_error("Create datawriter failed");
        }
    }

    void receiveLoop()
    {
        std::vector<uint8_t> buffer(65507);
        uint32_t data_size;

        while (running_) {  // 클래스 내부 running_ 대신 전역 running 변수 사용
            // 데이터 크기 수신
            ssize_t size_received = recv(sock, &data_size, sizeof(data_size), 0);
            if (size_received != sizeof(data_size) || !running) break;  // running 체크 추가
        
            data_size = ntohl(data_size);
        
            std::vector<uint8_t> jpeg_data;
            jpeg_data.resize(data_size);

            ssize_t received = recv(sock, jpeg_data.data(), data_size, MSG_WAITALL);

            if (received == static_cast<ssize_t>(data_size) && running) {  // running 체크 추가
              std::vector<uint8_t>& data_ref = jpeg_data;
               image_data_.data(data_ref);
              image_data_.width(640);
              image_data_.height(480);
              image_data_.encoding("jpeg");
            
              writer_->write(&image_data_);
         }
        }
    }

public:
    CameraServer(int port = 8485) : running_(false) {
        setupUDP(port);
        setupDDS();
    }

    void start() {
        running_ = true;
        receive_thread_ = std::thread(&CameraServer::receiveLoop, this);
        std::cout << "Camera server started. Listening on port 8485..." << std::endl;
    }

    void stop() {
        running_ = false;
        if (receive_thread_.joinable()) {
            receive_thread_.join();
        }
        close(sock);

        if (writer_ != nullptr) {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr) {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr) {
            participant_->delete_topic(topic_);
        }
        if (participant_ != nullptr) {
            DomainParticipantFactory::get_instance()->delete_participant(participant_);
        }
    }

    ~CameraServer() {
        stop();
    }
};

int main(int argc, char** argv) {

    // Signal Handler 등록
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    try {
        CameraServer server(8485);
        server.start();

        // running 플래그를 체크하는 루프로 변경
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        server.stop();
        std::cout << "Program terminated safely." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}