cmake_minimum_required(VERSION 3.26)
project(DS_Collection_Self_Made C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(Vector)

add_executable(DS_Collection_Self_Made
        Vector/vector.h
        Vector/vector_test_int.c
        utils.h)
