cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

add_subdirectory(commands)
include_directories(commands)

add_subdirectory(database)
include_directories(database)

# sources
set (SOURCE_FILES command_manager.cpp configuration_manager.cpp connection_manager.cpp context.cpp context_manager.cpp daemon.cpp delegate.cpp 
    hub.cpp iasync.cpp iconnection.cpp logger.cpp memory_manager.cpp signal_handler.cpp system.cpp telnet_connection.cpp 
    tcp_server.cpp telnet_server.cpp timer.cpp worker.cpp)

add_library(production ${SOURCE_FILES})



