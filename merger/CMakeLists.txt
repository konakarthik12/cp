cmake_minimum_required(VERSION 3.25)
project(merger)

set(CMAKE_CXX_STANDARD 17)

# Use the shared LLVM/clang install built from the inliner's submodule (see
# ~/.cache/caide-llvm-22.1.8-build) so no build tree compiles LLVM itself.
set(CAIDE_USE_SYSTEM_CLANG ON CACHE BOOL "" FORCE)
set(LLVM_DIR "$ENV{HOME}/.local/caide-llvm-22.1.8/lib/cmake/llvm" CACHE PATH "" FORCE)
set(Clang_DIR "$ENV{HOME}/.local/caide-llvm-22.1.8/lib/cmake/clang" CACHE PATH "" FORCE)

add_subdirectory(/Users/konak/Projects/caide-cpp-inliner/src inliner-output/)
include_directories("/Users/konak/Projects/caide-cpp-inliner/src")
add_executable(merger main.cpp)
add_dependencies(merger caideInliner)
target_link_libraries(merger caideInliner)
