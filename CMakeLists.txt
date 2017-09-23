cmake_minimum_required(VERSION 2.8.9)
project (hub)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

set(CMAKE_CXX_COMPILE_OBJECT "$(USE_DISTCC) <CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")

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

# check if sqlite3 is present
FIND_LIBRARY(SQLITE_LIB sqlite3)
IF(NOT SQLITE_LIB)
  MESSAGE(FATAL_ERROR "sqlite3 library not found")
ENDIF()

# sources
add_subdirectory(src)
include_directories(src)
include_directories(src/commands)
include_directories(src/database)
include_directories(src/tools)
include_directories(src/network)
add_executable(hub main.cpp)

# unit tests
add_subdirectory(unit_test)
include_directories(unit_test)
add_executable(ut test.cpp)

# linking
TARGET_LINK_LIBRARIES(hub production commands database network tools config++ sqlite3 socket++)
TARGET_LINK_LIBRARIES(ut production commands database network tools testing config++ sqlite3 socket++ /usr/lib/libgtest.a)
