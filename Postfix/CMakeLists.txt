cmake_minimum_required(VERSION 3.6)
project(Postfix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Postfix.cpp Postfix.h Node.h Stack.h)
add_executable(Postfix ${SOURCE_FILES})