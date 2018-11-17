cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(/root/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/account)
include_directories(${CMAKE_SOURCE_DIR}/src/network)
include_directories(${CMAKE_SOURCE_DIR}/src/machine)

# sources
set (SOURCE_FILES context_manager.cpp context.cpp mobile_connection.cpp mobile_messages.pb.cc tcp_base.cpp tcp_connection.cpp telnet_connection.cpp)

add_library(network ${SOURCE_FILES})