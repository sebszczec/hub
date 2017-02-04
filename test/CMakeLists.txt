cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# sources
set (SOURCE_FILES uptime_command_test.cpp)
add_library(testing ${SOURCE_FILES})


