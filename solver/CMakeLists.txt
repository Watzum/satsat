cmake_minimum_required(VERSION 3.8)

project(solver)

set(HEADER_FILES include/Dimacs.h include/DimacsReader.h
        include/DimacsFormatException.h
        include/Variable.h
        include/CNFFormula.h
        include/Clause.h)

set(SOURCE_FILES src/Dimacs.cpp src/DimacsReader.cpp
        src/CNFFormula.cpp
        src/Clause.cpp
        src/Variable.cpp)

add_library(solver_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})