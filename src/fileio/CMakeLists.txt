cmake_minimum_required(VERSION 3.3)

project(FileIO)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_serialization -O3")

set(HEADER_FILES
        fileio.h
        )

set(SOURCE_FILES
        fileio.cpp
        )

find_package(Boost 1.56 COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(FileIO STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(FileIO ${Boost_LIBRARIES})
