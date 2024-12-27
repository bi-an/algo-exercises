cmake_minimum_required(VERSION 3.0)
project(UNIT_TEST)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
link_directories(lib)

add_executable(testcase_example)
target_sources(testcase_example PRIVATE 
testcase_example.cpp
)
target_link_libraries(testcase_example -ljsoncpp)
target_compile_options(testcase_example PRIVATE -g -ggdb)
# target_compile_options(test_print PRIVATE -fdump-tree-all -fdump-ipa-all)

file(COPY ${CMAKE_SOURCE_DIR}/test_cases.json DESTINATION ${CMAKE_BINARY_DIR}/)
# configure_file(${CMAKE_SOURCE_DIR}/data.txt ${CMAKE_BINARY_DIR}/data.txt COPYONLY)
# execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/config.txt ${CMAKE_BINARY_DIR}/config/)
# install(FILES ${CMAKE_SOURCE_DIR}/src/config.txt DESTINATION ${CMAKE_INSTALL_PREFIX}/config/)

