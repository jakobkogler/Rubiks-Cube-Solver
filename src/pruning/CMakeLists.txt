cmake_minimum_required(VERSION 3.3)

project(Prune)

set(HEADER_FILES
        prune.h
        cornerPruning.h
        edgePruning.h
        nibble.h
        )

include_directories(../cube)

set(SOURCE_FILES
        prune.cpp
        cornerPruning.cpp
        edgePruning.cpp
        )

add_library(Prune STATIC ${SOURCE_FILES} ${HEADER_FILES})
