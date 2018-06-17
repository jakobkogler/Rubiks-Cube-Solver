cmake_minimum_required(VERSION 3.3)

project(FileIO)

set(HEADER_FILES
        fileio.h
        )

set(SOURCE_FILES
        fileio.cpp
        )

add_library(FileIO STATIC ${SOURCE_FILES} ${HEADER_FILES})
