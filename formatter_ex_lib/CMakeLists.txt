cmake_minimum_required(VERSION 3.4.0)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project( ex CXX )

add_library(formatter_ex STATIC formatter_ex.cpp formatter_ex.h)

set_target_properties(
	formatter_ex PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_include_directories(
	formatter_ex
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib
)

target_link_libraries(formatter_ex formatter)

