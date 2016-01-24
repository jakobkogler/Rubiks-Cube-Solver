cmake_minimum_required(VERSION 3.3)

project(Cube)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(HEADER_FILES
        prune.h
        cpPruning.h
        coPruning.h
        eoPruning.h
        )

include_directories(../cube)

set(SOURCE_FILES
        prune.cpp
        cpPruning.cpp
        coPruning.cpp
        eoPruning.cpp
        )

add_library(Prune STATIC ${SOURCE_FILES} ${HEADER_FILES})
