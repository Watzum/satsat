cmake_minimum_required(VERSION 3.8)
project(satsat)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

add_executable(satsat_run ${SOURCE_FILES})

include_directories(solver)
add_subdirectory(solver)

target_link_libraries(satsat_run solver_lib)

add_subdirectory(Google_tests)
