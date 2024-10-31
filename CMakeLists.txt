cmake_minimum_required(VERSION 3.29)
project(Lab_3___Pointers__References__Operator_Overloading)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab_3___Pointers__References__Operator_Overloading
    ContactBook.cpp
    ContactBook.h
        test_1.cpp
    test_2.cpp
    test_3.cpp
    test_4.cpp)
