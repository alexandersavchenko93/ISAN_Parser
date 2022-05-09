cmake_minimum_required(VERSION 3.20.1 FATAL_ERROR)

set(PROJECT_NAME ISANParser)
project(${PROJECT_NAME} C CXX)

SET(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_STANDARD 14)

enable_testing()

add_subdirectory(external/googletest)

set(Sources 
	src/main.cpp
)

add_library(${PROJECT_NAME} STATIC ${Sources})

add_subdirectory(test)

