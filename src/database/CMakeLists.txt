cmake_minimum_required(VERSION 2.8.9)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/database)

# sources
set (SOURCE_FILES database.cpp db_exceptions.cpp)

add_library(database ${SOURCE_FILES})