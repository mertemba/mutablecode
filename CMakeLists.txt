PROJECT(MutableCode)
cmake_minimum_required(VERSION 2.8)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

SET(SOURCES
	${PROJECT_SOURCE_DIR}/main.cpp
	${PROJECT_SOURCE_DIR}/Interpreter.cpp
)
SET(HEADERS
	${PROJECT_INCLUDE_DIR}/Tape.hpp
	${PROJECT_INCLUDE_DIR}/Program.hpp
	${PROJECT_INCLUDE_DIR}/Interpreter.hpp
)

ADD_EXECUTABLE(MutableCode ${SOURCES} ${HEADERS})
