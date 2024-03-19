cmake_minimum_required(VERSION 3.25)
project(merger)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(/Users/konak/Projects/randgit/caide-cpp-inliner/src inliner-output/)
include_directories("/Users/konak/Projects/randgit/caide-cpp-inliner/src")
add_executable(merger main.cpp)
add_dependencies(merger caideInliner)
target_link_libraries(merger caideInliner)
