cmake_minimum_required(VERSION 3.8)

project(solver)

set(HEADER_FILES include/Dimacs.h include/DimacsReader.h include/VariableClauseRelation.h
        include/DimacsFormatException.h)

set(SOURCE_FILES src/Dimacs.cpp src/DimacsReader.cpp src/VariableClauseRelation.cpp)

add_library(solver_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})