cmake_minimum_required(VERSION 3.6)
project(Circular_buffer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c circular_buffer.c circular_buffer.h)
add_executable(Circular_buffer ${SOURCE_FILES})