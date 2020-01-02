cmake_minimum_required(VERSION 3.10)
project(WordCount)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(WordCount main.cpp parser.hpp counter.hpp counter.hpp)
add_executable(Generator generator.cpp)