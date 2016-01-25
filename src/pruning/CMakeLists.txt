cmake_minimum_required(VERSION 3.3)

project(Cube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(HEADER_FILES
        prune.h
        cornerPruning.h
        cpPruning.h
        coPruning.h
        eoPruning.h
        epPruning.h
        ep2Pruning.h
        )

include_directories(../cube)

set(SOURCE_FILES
        prune.cpp
        cornerPruning.cpp
        cpPruning.cpp
        coPruning.cpp
        eoPruning.cpp
        epPruning.cpp
        ep2Pruning.cpp
        )

add_library(Prune STATIC ${SOURCE_FILES} ${HEADER_FILES})
