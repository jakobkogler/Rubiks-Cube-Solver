cmake_minimum_required(VERSION 3.3)

project(Optimal_Solver)

set(HEADER_FILES
        optimal_solver.h
        )

include_directories(cube)
include_directories(pruning)

set(SOURCE_FILES
        optimal_solver.cpp
        )

add_subdirectory(cube)

add_library(Optimal_Solver STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Optimal_Solver Cube)
