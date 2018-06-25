cmake_minimum_required(VERSION 3.3)

project(Cube)

set(HEADER_FILES
        cube.h
        group.h
        corner_orientation.h
        corner_permutation.h
        corners.h
        edges.h
        indexing.h
        pruning_info.h
        )

set(SOURCE_FILES
        cube.cpp
        group.cpp
        corner_orientation.cpp
        corner_permutation.cpp
        corners.cpp
        edges.cpp
        indexing.cpp
        )

add_library(Cube STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(Cube PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
