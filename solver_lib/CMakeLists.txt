cmake_minimum_required(VERSION 3.16.3)
project(solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver STATIC solver.cpp solver.h)