cmake_minimum_required(VERSION 3.21)
project(AI)

set(CMAKE_CXX_STANDARD 20)

add_executable(AI Source/main.cpp Headers/CSVRow.h Source/CSVRow.cpp Headers/Node.h Source/Node.cpp Source/Algorithms.cpp Headers/Algorithms.h)

file(GLOB_RECURSE RESOURSES_FILES resourses/*.png)
file(GLOB_RECURSE RESOURSES_FILES resourses/*.cvs)
file(GLOB_RECURSE RESOURSES_FILES resourses/*.ttf)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(AI sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
