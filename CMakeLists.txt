cmake_minimum_required(VERSION 3.10)
project(Prefix_tree_filter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
endif()

add_executable(Prefix_tree_filter 
    src/main.cpp 
    src/filter/filter.cpp
    src/utils/utils.cpp
    src/tree/prefix_tree.cpp
    src/tree/tree_operations.cpp
    src/tree/prefix_tree_node.cpp
)

target_include_directories(Prefix_tree_filter PUBLIC
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/filter
    ${PROJECT_SOURCE_DIR}/src/tree
    ${PROJECT_SOURCE_DIR}/src/utils
)