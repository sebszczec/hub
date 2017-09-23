cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

add_subdirectory(commands)
include_directories(commands)

add_subdirectory(database)
include_directories(database)

add_subdirectory(network)
include_directories(network)

add_subdirectory(tools)
include_directories(tools)

include_directories(${CMAKE_SOURCE_DIR}/src)

# sources
set (SOURCE_FILES configuration_manager.cpp daemon.cpp logger.cpp memory_manager.cpp signal_handler.cpp system.cpp)

add_library(production ${SOURCE_FILES})



