cmake_minimum_required(VERSION 3.8)

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_tests_run test1.cpp)

target_link_libraries(Google_tests_run solver_lib)

target_link_libraries(Google_tests_run gtest gtest_main)