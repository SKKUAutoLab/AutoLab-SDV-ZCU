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

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::types;

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

    void receiveLoop() {
        std::vector<uint8_t> buffer(65507);
        uint32_t data_size;

        while (running_) {
            // 데이터 크기 수신
            ssize_t size_received = recv(sock, &data_size, sizeof(data_size), 0);
            if (size_received != sizeof(data_size)) continue;
            
            data_size = ntohl(data_size);
            
            // JPEG 데이터 수신을 위한 벡터 준비
            std::vector<uint8_t> jpeg_data;
            jpeg_data.resize(data_size);

            // JPEG 데이터 수신
            ssize_t received = recv(sock, jpeg_data.data(), data_size, MSG_WAITALL);

            if (received == static_cast<ssize_t>(data_size)) {
                // FastDDS로 데이터 발행
                std::vector<uint8_t>& data_ref = jpeg_data;
                image_data_.data(data_ref);
                image_data_.width(640);
                image_data_.height(480);
                image_data_.encoding("jpeg");
                
                writer_->write(&image_data_);
                
                // std::cout << "Published image data: " << data_size << " bytes" << std::endl;
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
    try {
        CameraServer server(8485);
        server.start();

        // 메인 스레드는 여기서 대기
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();

        server.stop();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}