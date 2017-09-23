cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/system)

# sources
set (SOURCE_FILES configuration_manager.cpp daemon.cpp logger.cpp memory_manager.cpp signal_handler.cpp system.cpp)

add_library(system ${SOURCE_FILES})