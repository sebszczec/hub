cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# sources
set (SOURCE_FILES command_manager.cpp configuration_manager.cpp connection_manager.cpp daemon.cpp hub.cpp iasync.cpp logger.cpp memory_manager.cpp signal_handler.cpp system.cpp telnet_server.cpp timer.cpp uptime_command.cpp worker.cpp)
add_library(production ${SOURCE_FILES})


