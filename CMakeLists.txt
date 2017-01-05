cmake_minimum_required(VERSION 2.8.9)
project (hub)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# extra compilation flags
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

# check if libconfig is present
FIND_LIBRARY(CONFIG_LIB config++)
IF(NOT CONFIG_LIB)
  MESSAGE(FATAL_ERROR "libconfig++ library not found")
ENDIF()

# Locate GTest
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

# sources
add_subdirectory(src)
include_directories(src)
add_executable(hub main.cpp)

# linking
TARGET_LINK_LIBRARIES(hub production config++)

