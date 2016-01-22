cmake_minimum_required(VERSION 3.3)

project(Optimal_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_serialization -O3")

set(HEADER_FILES
        ../include/Collisionset.h
        ../include/corner.h
        ../include/corner_orientation.h
        ../include/corner_permutation.h
        ../include/edge_orientation.h
        ../include/edge_permutation.h
        ../include/group.h
        ../include/indexing.h
        ../include/optimal_solver.h
        ../include/read_store.h
        )

set(SOURCE_FILES
        Collisionset.cpp
        corner.cpp
        corner_orientation.cpp
        corner_permutation.cpp
        edge_orientation.cpp
        edge_permutation.cpp
        group.cpp
        indexing.cpp
        optimal_solver.cpp
        read_store.cpp
        )

find_package(Boost 1.56 COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_library(Optimal_Solver STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(Optimal_Solver ${Boost_LIBRARIES})
