cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/tools)

# sources
set (SOURCE_FILES delegate.cpp iasync.cpp timer.cpp worker.cpp)

add_library(tools ${SOURCE_FILES})