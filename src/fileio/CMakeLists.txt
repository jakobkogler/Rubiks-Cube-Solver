cmake_minimum_required(VERSION 3.3)

project(FileIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(HEADER_FILES
        fileio.h
        )

set(SOURCE_FILES
        fileio.cpp
        )

add_library(FileIO STATIC ${SOURCE_FILES} ${HEADER_FILES})
