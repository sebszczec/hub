cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# sources
set (SOURCE_FILES configuration_manager.cpp daemon.cpp hub.cpp iasync.cpp logger.cpp signal_handler.cpp telnet_server.cpp timer.cpp uptime_command.cpp worker.cpp)
add_library(production ${SOURCE_FILES})


