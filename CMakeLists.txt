cmake_minimum_required(VERSION 3.17)
project(mark_sweep_gc)

set(CMAKE_CXX_STANDARD 17)

add_executable(mark_sweep_gc main.cpp vm.cpp obj.cpp)
