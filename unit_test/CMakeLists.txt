cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# headers with classes to be tested
include_directories(test)

include_directories(${CMAKE_SOURCE_DIR}/src/commands)
include_directories(${CMAKE_SOURCE_DIR}/src/tools)


# test sources
set (SOURCE_FILES connection_manager_test.cpp context_manager_test.cpp delegate_test.cpp help_command_test.cpp memory_manager_test.cpp system_test.cpp 
    telnet_connection_test.cpp uptime_command_test.cpp)
add_library(testing ${SOURCE_FILES})


