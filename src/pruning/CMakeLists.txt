cmake_minimum_required(VERSION 3.3)

project(Prune)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(HEADER_FILES
        prune.h
        cornerPruning.h
        cpPruning.h
        coPruning.h
        eoPruning.h
        ep1Pruning.h
        ep2Pruning.h
        edgePruning.h
        Phase1Pruning.h
        )

include_directories(../cube)
include_directories(../fileio)

set(SOURCE_FILES
        prune.cpp
        cornerPruning.cpp
        cpPruning.cpp
        coPruning.cpp
        eoPruning.cpp
        ep1Pruning.cpp
        ep2Pruning.cpp
        edgePruning.cpp
        Phase1Pruning.cpp
        )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../fileio ${CMAKE_CURRENT_BINARY_DIR}/fileio)

add_library(Prune STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Prune FileIO)
