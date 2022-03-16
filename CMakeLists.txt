cmake_minimum_required(VERSION 3.21)
project(AI)

set(CMAKE_CXX_STANDARD 20)

add_executable(AI Source/main.cpp Headers/CSVRow.h Source/CSVRow.cpp Headers/Node.h Source/Node.cpp Source/Algorithms.cpp Headers/Algorithms.h)
