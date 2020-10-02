cmake_minimum_required(VERSION 3.16)
project(Codes)

set(CMAKE_CXX_STANDARD 17)

add_executable(Codes src/main.cpp src/Matrix.cpp include/Matrix.h src/LinearSolver.cpp include/LinearSolver.h src/Vec.cpp include/Vec.h src/chap1.cpp src/Timer.cpp include/Timer.h)