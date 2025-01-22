cmake_minimum_required(VERSION 3.12.4)
project(zcu)

# Find required packages
find_package(FastRTPS REQUIRED)
find_package(fastcdr REQUIRED)

# Set include directories for all targets
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/camera_module
    ${PROJECT_SOURCE_DIR}/include/control_module
    ${FastRTPS_INCLUDE_DIR}
    ${fastcdr_INCLUDE_DIR}
)

# Add source files for camera module
set(CAMERA_SOURCES
    src/camera_module/camera_server.cpp
    src/camera_module/Image.cxx
    src/camera_module/ImagePubSubTypes.cxx
)

# Add source files for control module
set(CONTROL_SOURCES
    src/control_module/control_subscriber.cpp
    src/control_module/ControlCommand.cxx
    src/control_module/ControlCommandPubSubTypes.cxx
    src/control_module/s32g3_skku_can_setting.c
)

# Create executable
add_executable(zcu 
    src/main.cpp
    ${CAMERA_SOURCES}
    ${CONTROL_SOURCES}
)

# Link libraries
target_link_libraries(zcu
    fastrtps 
    fastcdr
    pthread
)