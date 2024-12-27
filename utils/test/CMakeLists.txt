cmake_minimum_required(VERSION 3.0)
project(UNIT_TEST)
set(CMAKE_CXX_STANDARD 20)

# include_directories(.. ../../3party/json/include/nlohmann ../../3party/json/include)
include_directories(.. ../3party/json/include)

# add_executable(test_list test_list.cpp)

# add_executable(test_print test_print.cpp)
# target_compile_options(test_print PRIVATE -fdump-tree-all -fdump-ipa-all)

add_executable(testcase_example)
target_sources(testcase_example PRIVATE 
../testcase_example.cpp
)