cmake_minimum_required(VERSION 3.26)
project(cp)


add_definitions(-DEDITOR -DDEBUG)
set(CMAKE_CXX_STANDARD 20)
add_executable(cp template.cpp main.cpp
        testing/DocTestExtension.cpp
        testing/DocTestExtension.h
        testing/tests.cpp)