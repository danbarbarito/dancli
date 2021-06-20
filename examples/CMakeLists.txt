cmake_minimum_required(VERSION 3.5)

project(dancli-examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(dancli-example1 src/example1.cpp)
target_link_libraries(dancli-example1 dancli)

