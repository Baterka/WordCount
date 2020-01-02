cmake_minimum_required(VERSION 3.10)
project(WordCount)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

# Main
add_executable(WordCount main.cpp parser.hpp counter.hpp)
add_executable(Generator generator.cpp)

# Tests
add_executable(WordCountTests tests/tests-main.cpp tests/tests-counter.cpp counter.hpp)