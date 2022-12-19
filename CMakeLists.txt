cmake_minimum_required(VERSION 3.23)
project(TermProject_SHA256)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(TermProject_SHA256 main.cpp)
