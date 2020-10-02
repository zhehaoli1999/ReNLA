cmake_minimum_required(VERSION 3.16)
project(Codes)

set(CMAKE_CXX_STANDARD 17)

add_executable(Codes main.cpp Matrix.cpp Matrix.h LinearSolver.cpp LinearSolver.h Vec.cpp Vec.h)