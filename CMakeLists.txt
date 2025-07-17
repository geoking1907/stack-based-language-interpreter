cmake_minimum_required(VERSION 3.31)
project(stack_based_language_interpreter)

set(CMAKE_CXX_STANDARD 20)

add_executable(stack_based_language_interpreter main.cpp program.ssb)
