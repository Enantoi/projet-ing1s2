cmake_minimum_required(VERSION 3.29)
project(FondAquatique)

set(CMAKE_CXX_STANDARD 20)

add_executable(FondAquatique main.cpp)
target_link_libraries(FondAquatique -lmingw32 -lalleg44)
