cmake_minimum_required(VERSION 3.3)

project(Optimal_Solver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_serialization -O3")

set(HEADER_FILES
        optimal_solver.h
        )

include_directories(cube)

set(SOURCE_FILES
        optimal_solver.cpp
        )

add_subdirectory(cube)

#find_package(Boost 1.56 COMPONENTS serialization REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

add_library(Optimal_Solver STATIC ${SOURCE_FILES} ${HEADER_FILES})
#target_link_libraries(Optimal_Solver ${Boost_LIBRARIES} Cube)
target_link_libraries(Optimal_Solver Cube)
