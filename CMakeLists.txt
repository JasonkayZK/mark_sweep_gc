cmake_minimum_required(VERSION 3.17)
project(mark_sweep_gc)

set(CMAKE_CXX_STANDARD 11)

add_executable(mark_sweep_gc main.cpp vm/vm.cpp obj/obj.cpp)
