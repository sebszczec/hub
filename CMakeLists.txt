cmake_minimum_required(VERSION 2.8.9)
project (hub)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# extra compilation flags
# -g - generates debug symbols
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -g")

# check if libconfig is present
FIND_LIBRARY(CONFIG_LIB config++)
IF(NOT CONFIG_LIB)
  MESSAGE(FATAL_ERROR "libconfig++ library not found")
ENDIF()

# Locate GTest
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

# check if libsocket is present
FIND_LIBRARY(SOCKET_LIB socket++)
IF(NOT SOCKET_LIB)
  MESSAGE(FATAL_ERROR "libsocket++ library not found")
ENDIF()

# sources
add_subdirectory(src)
include_directories(src)
add_executable(hub main.cpp)

# unit tests
add_subdirectory(unit_test)
include_directories(unit_test)
add_executable(ut test.cpp)

# linking
TARGET_LINK_LIBRARIES(hub production config++ socket++)
TARGET_LINK_LIBRARIES(ut production testing config++ gtest socket++)
