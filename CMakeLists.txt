cmake_minimum_required(VERSION 3.28)

project(locus LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(locus INTERFACE)

target_include_directories( locus INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_executable(geometry_tests
    tests/geometry_tests.cpp
)

target_link_libraries(geometry_tests PRIVATE locus)

add_test(NAME geometry_tests COMMAND geometry_tests)