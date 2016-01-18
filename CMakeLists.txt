cmake_minimum_required(VERSION 3.3)
project(Rubiks_Cube_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_serialization -O3")

set(SOURCE_FILES
    src/corner.cpp
    src/corner.h
    src/corner_orientation.cpp
    src/corner_orientation.h
    src/corner_permutation.cpp
    src/corner_permutation.h
    src/edge_orientation.cpp
    src/edge_orientation.h
    src/edge_permutation.cpp
    src/edge_permutation.h
    src/group.cpp
    src/group.h
    src/indexing.cpp
    src/indexing.h
    src/optimal_solver.cpp
    src/optimal_solver.h
    src/read_store.cpp
    src/read_store.h
    src/test.cpp)

find_package(Boost 1.60 COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(Rubiks_Cube_Solver ${SOURCE_FILES})

target_link_libraries(Rubiks_Cube_Solver ${Boost_LIBRARIES})
