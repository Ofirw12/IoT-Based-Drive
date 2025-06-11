cmake_minimum_required(VERSION 3.20)
project(iot_drive)


set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED 17)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-pedantic-errors -Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG -g)
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3")
set(CMAKE_C_EXTENSIONS OFF)

add_subdirectory(framework)
add_subdirectory(concrete)
