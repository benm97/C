cmake_minimum_required(VERSION 3.8)
project(ex3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        calculator.c
        calculator.h
        heat_eqn.c
        heat_eqn.h
        reader.c)

add_executable(ex3 ${SOURCE_FILES})