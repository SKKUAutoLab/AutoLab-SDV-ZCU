cmake_minimum_required(VERSION 3.12.4)
project(control_subscriber)

# Find FastDDS and FastCDR
find_package(FastRTPS REQUIRED)
find_package(fastcdr REQUIRED)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${FastRTPS_INCLUDE_DIR}
    ${fastcdr_INCLUDE_DIR}
)

# Create executable
add_executable(control_sub 
    ControlSubscriber.cpp
    ControlCommand.cxx
    ControlCommandPubSubTypes.cxx
    s32g3_skku_can_setting.c
)

# Link libraries
target_link_libraries(control_sub 
    fastrtps 
    fastcdr
)