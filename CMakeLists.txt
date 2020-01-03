cmake_minimum_required(VERSION 3.5)
project(WordCount LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(WordCount main.cpp parser.hpp counter.hpp)
add_executable(Generator generator.cpp)
add_executable(Tests tests/tests-main.cpp tests/tests-counter.cpp counter.hpp)

SET(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(WordCount Threads::Threads)
target_link_libraries(Tests Threads::Threads)