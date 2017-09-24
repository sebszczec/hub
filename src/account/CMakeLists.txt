cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/account)

# sources
set (SOURCE_FILES access_state.cpp account_manager.cpp user.cpp)

add_library(account ${SOURCE_FILES})