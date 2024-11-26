cmake_minimum_required(VERSION 3.29)
project(vector_implementation)

set(CMAKE_CXX_STANDARD 20)

add_executable(vector_implementation main.cpp
        vector.h
        test_vector.h)
