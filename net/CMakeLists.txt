cmake_minimum_required(VERSION 3.0)

project(net)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

include_directories(lib)

set(DIRS lib select ) # poll epoll

foreach(dir IN LISTS DIRS)
    message(STATUS "add_subdirectory ${dir}")
    add_subdirectory(${dir})
endforeach()
