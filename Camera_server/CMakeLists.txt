cmake_minimum_required(VERSION 3.12.4)
project(camera_server)

# Find FastDDS and FastCDR
find_package(FastRTPS REQUIRED)
find_package(fastcdr REQUIRED)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}
    ${FastRTPS_INCLUDE_DIR}
    ${fastcdr_INCLUDE_DIR}
)

# Add source files
add_executable(camera_server 
    main.cpp
    Image.cxx
    ImagePubSubTypes.cxx
)

# Link libraries
target_link_libraries(camera_server 
    fastrtps 
    fastcdr
    pthread
)