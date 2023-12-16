cmake_minimum_required(VERSION 3.13)

project(pypp_aoclib)


# google test
include(FetchContent)
FetchContent_Declare(gtest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1)
FetchContent_GetProperties(gtest)
if (NOT gtest_POPULATED)
    FetchContent_Populate(gtest)
    add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BUILD_DIR})
endif()

# lib to test
add_library(Pypp STATIC pypp.cpp)

# executables
add_executable(pypp_test test/pypp_test.cpp)
target_link_libraries(pypp_test Pypp gtest_main gmock_main)
