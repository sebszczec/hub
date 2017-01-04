cmake_minimum_required(VERSION 2.8.9)
project (hub)

# enable C++14 standard
set(CMAKE_CXX_STANDARD 14)  

# check if libconfig is present
FIND_LIBRARY(CONFIG_LIB config++)
IF(NOT CONFIG_LIB)
  MESSAGE(FATAL_ERROR "libconfig++ library not found")
ENDIF()

# sources
set (SOURCE_FILES daemon.cpp hub.cpp logger.cpp main.cpp)
add_executable(hub ${SOURCE_FILES})

# linking
TARGET_LINK_LIBRARIES(hub config++)

