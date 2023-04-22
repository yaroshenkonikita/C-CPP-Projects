cmake_minimum_required(VERSION 3.22)

project(Matrix VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Matrix
               matrix_oop.cc
               matrix_oop.h)
