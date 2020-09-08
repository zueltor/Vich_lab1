cmake_minimum_required(VERSION 3.15)
project(lab1cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab1cpp main.cpp equation.cpp)
add_executable(lab1test test.cpp equation.cpp)