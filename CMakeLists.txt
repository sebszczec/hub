cmake_minimum_required(VERSION 2.8.9)
project (hub)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# Debug or release
set(CMAKE_BUILD_TYPE Debug)

# Allows to use distcc for cloud computing
# set(CMAKE_CXX_COMPILE_OBJECT "$(USE_DISTCC) <CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")

# extra compilation flags
# -g - generates debug symbols
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread -Wall -fprofile-arcs -ftest-coverage")

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

# Prepare files to be handled by gcov (*.cpp.gcno -> *.gcno)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

# check if libconfig is present
FIND_LIBRARY(CONFIG_LIB config++)
IF(NOT CONFIG_LIB)
  MESSAGE(FATAL_ERROR "libconfig++ library not found")
ENDIF()

# Locate GTest
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})

# check if sqlite3 is present
FIND_LIBRARY(SQLITE_LIB sqlite3)
IF(NOT SQLITE_LIB)
  MESSAGE(FATAL_ERROR "sqlite3 library not found")
ENDIF()

# sources
add_subdirectory(src)
include_directories(include)
include_directories(src)
include_directories(src/account)
include_directories(src/commands)
include_directories(src/database)
include_directories(src/tools)
include_directories(src/network)
include_directories(src/machine)
add_executable(hub main.cpp)

# unit tests
add_subdirectory(unit_test)
include_directories(unit_test)
add_executable(ut test.cpp)

# linking
TARGET_LINK_LIBRARIES(hub machine commands network tools config++ account database sqlite3)
  
TARGET_LINK_LIBRARIES(ut machine account commands database network tools testing config++ sqlite3 /usr/lib/libgtest.a)
