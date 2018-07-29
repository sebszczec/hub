cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/account)
include_directories(${CMAKE_SOURCE_DIR}/src/commands)
include_directories(${CMAKE_SOURCE_DIR}/src/database)
include_directories(${CMAKE_SOURCE_DIR}/src/machine)
include_directories(${CMAKE_SOURCE_DIR}/src/network)

# sources
set (SOURCE_FILES command_manager.cpp help_command.cpp login_command.cpp logout_command.cpp ls_command.cpp uptime_command.cpp whoami_command.cpp)

add_library(commands ${SOURCE_FILES})