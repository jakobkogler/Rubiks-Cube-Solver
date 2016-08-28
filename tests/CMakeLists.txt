project(solver_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        cube_tests/corner_orientation_test.cpp
        )

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(../src/cube)

add_executable(solver_tests ${SOURCE_FILES})

target_link_libraries(solver_tests Cube ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})