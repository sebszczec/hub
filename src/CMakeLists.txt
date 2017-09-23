cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

add_subdirectory(commands)
include_directories(commands)

add_subdirectory(database)
include_directories(database)

add_subdirectory(tools)
include_directories(tools)

# sources
set (SOURCE_FILES configuration_manager.cpp connection_manager.cpp context.cpp context_manager.cpp daemon.cpp iconnection.cpp 
    logger.cpp memory_manager.cpp signal_handler.cpp system.cpp telnet_connection.cpp tcp_server.cpp telnet_server.cpp)

add_library(production ${SOURCE_FILES})



