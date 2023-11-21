cmake_minimum_required(VERSION 3.26)
project(DS_Collection_Self_Made C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(src)

add_executable(DS_Collection_Self_Made
        src/Vector/vector.h
        src/Vector/vector_test_int.c
        src/utils.h)
