cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/account)
include_directories(${CMAKE_SOURCE_DIR}/src/network)
include_directories(${CMAKE_SOURCE_DIR}/src/machine)

# sources
set (SOURCE_FILES context_manager.cpp context.cpp)

add_library(network ${SOURCE_FILES})