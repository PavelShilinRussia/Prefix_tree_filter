cmake_minimum_required(VERSION 3.10)
project(Prefix_tree_filter)
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

add_executable(Prefix_tree_filter 
src/main.cpp 
src/filter/filter.cpp
src/utils/utils.cpp
src/tree/prefix_tree.cpp
)


target_include_directories(Prefix_tree_filter PUBLIC
	${PROJECT_SOURCE_DIR}/src
)