cmake_minimum_required(VERSION 3.28)

project(locus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(locus INTERFACE)

target_include_directories( locus INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# EXE 1
add_executable(
    locus_visualizer 
    src/visualizer.cpp
)
target_link_libraries(
    locus_visualizer 
    PRIVATE locus
)

# EXE 2
add_executable(
    locus_solver 
    src/solver.cpp
)
target_link_libraries(
    locus_solver 
    PRIVATE locus
)