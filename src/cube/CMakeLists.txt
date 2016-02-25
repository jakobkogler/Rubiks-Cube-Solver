cmake_minimum_required(VERSION 3.3)

project(Cube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(HEADER_FILES
        cube.h
        group.h
        corner_orientation.h
        corner_permutation.h
        edge_orientation.h
        edge_permutation.h
        indexing.h
        )

set(SOURCE_FILES
        cube.cpp
        group.cpp
        corner_orientation.cpp
        corner_permutation.cpp
        edge_orientation.cpp
        edge_permutation.cpp
        indexing.cpp
        )

add_library(Cube STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(Cube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
