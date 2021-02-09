cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES battleships.c battleships_game.c battleships.h)
add_executable(ex2 ${SOURCE_FILES})