cmake_minimum_required(VERSION 3.5)
project(cp)


add_compile_definitions(DEBUG)
set(CMAKE_CXX_STANDARD 20)
add_executable(cp template.cpp)
add_executable(internal main.cpp testing/tests.cpp)

add_executable(tests template.cpp testing/doctest.h testing/DocTestExtension.h)
target_compile_definitions(cp PUBLIC ENTRY=main)

target_compile_definitions(tests PUBLIC ENTRY=testing/tests)

add_subdirectory(merger build/cmake/merger/)
