cmake_minimum_required(VERSION 3.18.4)
project(SAND-e VERSION 1.0.0)

add_library(
    robot
    ../include/robot.hpp
    ../include/robot.cpp
)
add_executable(SAND-e ../src/main.cpp)

target_link_libraries(SAND-e PRIVATE robot)