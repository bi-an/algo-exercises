cmake_minimum_required(VERSION 3.0)
project(UNIT_TEST)
set(CMAKE_CXX_STANDARD 20)

include_directories(..)

add_executable(test_list test_list.cpp)

add_executable(test_print test_print.cpp)
# target_compile_options(test_print PRIVATE -fdump-tree-all -fdump-ipa-all)