cmake_minimum_required(VERSION 3.13)
project(satsat)
include_directories(include)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES src/main.cpp src/DimacsReader.cpp src/Dimacs.cpp src/VariableClauseRelation.cpp)

add_executable(satsat_run ${SOURCE_FILES})

