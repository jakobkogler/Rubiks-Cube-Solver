cmake_minimum_required(VERSION 3.3)

project(Prune)

set(HEADER_FILES
        prune.h
        cornerPruning.h
        cpPruning.h
        coPruning.h
        eoPruning.h
        ep1Pruning.h
        ep2Pruning.h
        edgePruning.h
        edgePruning2.h
        nibble.h
        )

include_directories(../cube)

set(SOURCE_FILES
        prune.cpp
        cornerPruning.cpp
        cpPruning.cpp
        coPruning.cpp
        eoPruning.cpp
        ep1Pruning.cpp
        ep2Pruning.cpp
        edgePruning.cpp
        edgePruning2.cpp
        )

add_library(Prune STATIC ${SOURCE_FILES} ${HEADER_FILES})
