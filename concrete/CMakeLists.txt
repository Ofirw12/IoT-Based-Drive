cmake_minimum_required(VERSION 3.20)
project(concrete)

include_directories(include)
include_directories(../../../cpp/include)
include_directories(../framework/include)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(test)
