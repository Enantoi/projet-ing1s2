cmake_minimum_required(VERSION 3.29)
project(BADLAND C)

set(CMAKE_C_STANDARD 11)

add_executable(BADLAND main.c)
target_link_libraries(BADLAND -lmingw32 -lalleg44)
