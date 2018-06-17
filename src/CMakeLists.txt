cmake_minimum_required(VERSION 3.3)

project(Optimal_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(HEADER_FILES
        optimal_solver.h
        )

include_directories(cube)
include_directories(pruning)

set(SOURCE_FILES
        optimal_solver.cpp
        )

add_subdirectory(cube)
add_subdirectory(pruning)

add_library(Optimal_Solver STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Optimal_Solver Cube Prune)
