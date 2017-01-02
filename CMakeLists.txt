cmake_minimum_required(VERSION 2.8.9)
project (hub)
set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard
set (SOURCE_FILES hub.cpp main.cpp)
add_executable(hub ${SOURCE_FILES})

