cmake_minimum_required(VERSION 3.5)

project(dancli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost 1.75.0 REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})


set(SOURCES src/cli.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(dancli ${SOURCES})
target_link_libraries(dancli ${Boost_LIBRARIES} ${SQLite3_LIBRARIES})


# Build examples
add_subdirectory(examples/)
