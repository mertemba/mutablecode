PROJECT(MutableCode)
cmake_minimum_required(VERSION 2.8)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

SET(MutableCode_SOURCES ${PROJECT_SOURCE_DIR}/main.cpp)
SET(MutableCode_HEADERS ${PROJECT_INCLUDE_DIR}/Tape.hpp)

ADD_EXECUTABLE(MutableCode ${MutableCode_SOURCES} ${MutableCode_HEADERS})

#TARGET_LINK_LIBRARIES(MutableCode)
