cmake_minimum_required(VERSION 3.20)
project(framework)

include_directories(include)
include_directories(../../../cpp/include)
include_directories(../concrete/include)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)
