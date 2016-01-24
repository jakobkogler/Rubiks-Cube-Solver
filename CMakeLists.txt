cmake_minimum_required(VERSION 3.3)

project(Rubiks_Cube_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(SOURCE_FILES main.cpp)
add_executable(Rubiks_Cube_Solver ${SOURCE_FILES})

include_directories(src)
include_directories(src/cube)
include_directories(src/pruning)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(Rubiks_Cube_Solver Optimal_Solver)
