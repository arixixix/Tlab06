cmake_minimum_required(VERSION 3.4)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(hell CXX)

add_executable(hell hello_world.cpp)

set_target_properties(
	hell PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)


target_include_directories(hell
	PUBLIC
	../formatter_ex_lib
)

target_link_libraries(hell formatter_ex)
