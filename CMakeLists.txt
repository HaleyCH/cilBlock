cmake_minimum_required(VERSION 3.20)
project(cilBlock)

set(CMAKE_CXX_STANDARD 14)

add_executable(cilBlock main.cpp Tool.cpp Tool.h GameManager.cpp GameManager.h)
