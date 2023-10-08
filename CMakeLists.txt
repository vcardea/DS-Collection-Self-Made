cmake_minimum_required(VERSION 3.26)
project(DSA_Collection_Self_Made C)

set(CMAKE_C_STANDARD 11)

include_directories(Vector)

add_executable(DSA_Collection_Self_Made
        Vector/vector.h
        test.c)
