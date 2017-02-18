cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# headers with classes to be tested
include_directories(test)

# test sources
set (SOURCE_FILES memory_manager_test.cpp system_test.cpp uptime_command_test.cpp)
add_library(testing ${SOURCE_FILES})


