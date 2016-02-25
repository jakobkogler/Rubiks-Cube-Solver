include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCubeTests
        corner_orientation_test.cpp)

target_link_libraries(runCubeTests gtest gtest_main Cube)
