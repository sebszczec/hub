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
set (SOURCE_FILES access_level.cpp account_manager.cpp user.cpp)

add_library(account ${SOURCE_FILES})