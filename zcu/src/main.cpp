#include "camera_module/camera_server.hpp"
#include "control_module/control_subscriber.hpp"
#include <signal.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

std::atomic<bool> running(true);

void signalHandler(int signum) {
    if (signum == SIGTERM || signum == SIGINT) {
        running = false;
    }
}

int main(int argc, char** argv) {
    // Register signal handler
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    try {
        // Create instances of both modules
        CameraServer camera_server(8485);
        ControlSubscriber control_subscriber;

        // Start both modules
        if (!camera_server.start()) {
            std::cerr << "Failed to start camera server" << std::endl;
            return 1;
        }

        if (!control_subscriber.start()) {
            std::cerr << "Failed to start control subscriber" << std::endl;
            camera_server.stop();
            return 1;
        }

        std::cout << "Both modules started successfully." << std::endl;

        // Main loop
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Clean shutdown
        std::cout << "Shutting down..." << std::endl;
        
        control_subscriber.sendShutdownMessages();
        control_subscriber.stop();
        camera_server.stop();
        
        std::cout << "Program terminated safely." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}