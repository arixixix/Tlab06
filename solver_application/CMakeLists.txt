cmake_minimum_required(VERSION 3.16.3)
project(equation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(equation equation.cpp)

target_include_directories(equation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib)
target_include_directories(equation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib)

target_link_libraries(equation formatter_ex)
target_link_libraries(equation solver)


include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "solver")
set(CPACK_PACKAGE_VENDOR "Arixixix")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

option(GENERATOR "")

if(${GENERATOR} MATCHES BINARY)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Arixixix")
install(TARGETS solver DESTINATION bin)
endif()

if(${GENERATOR} MATCHES ARCHIVE)
install(FILES equation.cpp 
                ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib/formatter.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib/formatter_ex.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib/solver.cpp
		DESTINATION files)
install(TARGETS formatter_ex solver LIBRARY DESTINATION libraries)
endif()

include(CPack)

