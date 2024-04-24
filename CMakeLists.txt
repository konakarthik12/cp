cmake_minimum_required(VERSION 3.5)
project(cp)
include(ExternalProject)

set(CMAKE_CXX_STANDARD 20)
add_executable(cp template.cpp)

add_executable(internal_main main.cpp)
add_executable(internal_testing testing/tests.cpp)

target_compile_definitions(cp PUBLIC ENTRY=main)

add_executable(tests template.cpp)
target_compile_definitions(tests PUBLIC ENTRY=testing/tests)
ExternalProject_Add(doctest
        GIT_REPOSITORY git@github.com:doctest/doctest.git
        PREFIX ${CMAKE_BINARY_DIR}/doctest
        UPDATE_COMMAND ${GIT_EXECUTABLE} pull
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
)

message(STATUS "Root directory of doctest: ${DOCTEST_INCLUDE_DIR}")
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

add_dependencies(tests doctest)
target_include_directories(tests PUBLIC ${DOCTEST_INCLUDE_DIR})
target_include_directories(internal_testing PUBLIC ${DOCTEST_INCLUDE_DIR})

add_subdirectory(merger build/cmake/merger/)