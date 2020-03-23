cmake_minimum_required(VERSION 3.5)

add_definitions("-fno-access-control -fsanitize=address -fsanitize=leak -O1 -Wall -ggdb3")
#add_definitions("-fno-access-control -fprofile-arcs -ftest-coverage -O1 -Wall -ggdb3")
#add_definitions("-fno-access-control -fsanitize=thread -O1 -Wall -ggdb3")
include_directories(BEFORE ${CMAKE_SOURCE_DIR}/include)

add_executable(gtest_LinkedList gtest_LinkedList.cpp)
target_link_libraries(gtest_LinkedList gtest gtest_main asan)
#target_link_libraries(gtest_LinkedList gtest gtest_main gcov)
#target_link_libraries(gtest_LinkedList gtest gtest_main tsan)

add_executable(gtest_Stack gtest_Stack.cpp)
target_link_libraries(gtest_Stack gtest gtest_main asan)
#target_link_libraries(gtest_Stack gtest gtest_main gcov)
#target_link_libraries(gtest_Stack gtest gtest_main tsan)

add_executable(gtest_Queue gtest_Queue.cpp)
target_link_libraries(gtest_Queue gtest gtest_main asan)
#target_link_libraries(gtest_Queue gtest gtest_main gcov)
#target_link_libraries(gtest_Queue gtest gtest_main tsan)

add_executable(gtest_Collection gtest_Collection.cpp)
target_link_libraries(gtest_Collection gtest gtest_main asan)
#target_link_libraries(gtest_Collection gtest gtest_main gcov)
#target_link_libraries(gtest_Collection gtest gtest_main tsan)
