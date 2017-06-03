cmake_minimum_required(VERSION 3.8.0)
project(algorithms)

include_directories(include)

file(GLOB SOURCES "src/*.c")
file(GLOB TESTS ${SOURCES} "tests/*.c")
list(REMOVE_ITEM TESTS "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")

add_executable(main ${SOURCES})
add_executable(tests ${TESTS})

