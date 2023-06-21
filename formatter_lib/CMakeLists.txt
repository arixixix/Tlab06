cmake_minimum_required(VERSION 3.12)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(formatter)

set(CMAKE_CXX_STANDART 17)

add_library(${PROJECT_NAME} STATIC
             formatter.cpp)

