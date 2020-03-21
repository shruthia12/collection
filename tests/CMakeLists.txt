cmake_minimum_required(VERSION 3.5)

add_definitions("-fno-access-control")
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/include)

add_executable(gtest_Stack gtest_Stack.cpp)
target_link_libraries(gtest_Stack gtest pthread)
