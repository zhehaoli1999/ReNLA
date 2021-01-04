cmake_minimum_required(VERSION 3.7)
project(Codes)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
add_executable(Chap1 src/Matrix.cpp include/Matrix.h src/LinearSolver.cpp include/LinearSolver.h src/Vec.cpp include/Vec.h src/chap1.cpp src/Timer.cpp include/Timer.h)
add_executable(Chap2 src/Matrix.cpp include/Matrix.h src/LinearSolver.cpp include/LinearSolver.h src/Vec.cpp include/Vec.h src/chap2.cpp src/Timer.cpp include/Timer.h)
add_executable(Chap3 include/LSSolver.h src/LSSolver.cpp src/Matrix.cpp src/LinearSolver.cpp src/Vec.cpp src/chap3.cpp src/Timer.cpp)
add_executable(Chap4 include/SparseMatrix.h src/SparseMatrix.cpp include/IterativeSolver.h src/IterativeSolver.cpp src/Matrix.cpp src/LinearSolver.cpp src/Vec.cpp src/chap4.cpp src/Timer.cpp)
add_executable(Chap5 include/SparseMatrix.h src/SparseMatrix.cpp include/IterativeSolver.h src/IterativeSolver.cpp src/Matrix.cpp src/LinearSolver.cpp src/Vec.cpp src/chap5.cpp src/Timer.cpp)
add_executable(Chap6 include/LSSolver.h src/LSSolver.cpp  src/LinearSolver.cpp include/LinearSolver.h include/EigenSolver.h src/EigenSolver.cpp include/IterativeSolver.h src/Matrix.cpp src/Vec.cpp src/chap6.cpp src/Timer.cpp)
add_executable(Chap7 src/chap7.cpp include/SymmetricEigenSolver.h src/SymmetricEigenSolver.cpp)

find_library(GTEST libgtest.a  ./include)
find_library(GTEST_MAIN libgtest_main.a  ./lib)

add_executable(Test include/Vec.h src/Vec.cpp test/VecTest.cpp
        include/Matrix.h src/Matrix.cpp test/MatrixTest.cpp  src/LinearSolver.cpp )

add_executable(SparseMatrixTest include/Vec.h src/Vec.cpp include/Matrix.h src/Matrix.cpp  include/SparseMatrix.h src/SparseMatrix.cpp test/SparseMatrixTest.cpp )
add_executable(LSSolverTest include/Vec.h src/Vec.cpp include/LinearSolver.h src/LinearSolver.cpp include/Matrix.h src/Matrix.cpp  include/LSSolver.h src/LSSolver.cpp test/LSSolverTest.cpp )
add_executable(EigenSolverTest include/LSSolver.h src/LSSolver.cpp src/LinearSolver.cpp include/Vec.h src/Vec.cpp include/Matrix.h src/Matrix.cpp include/EigenSolver.h src/EigenSolver.cpp test/EigenSolverTest.cpp)

target_link_libraries(SparseMatrixTest PUBLIC ${GTEST})
target_link_libraries(SparseMatrixTest PUBLIC ${GTEST_MAIN})

target_link_libraries(LSSolverTest PUBLIC ${GTEST})
target_link_libraries(LSSolverTest PUBLIC ${GTEST_MAIN})

target_link_libraries(EigenSolverTest PUBLIC ${GTEST})
target_link_libraries(EigenSolverTest PUBLIC ${GTEST_MAIN})

target_link_libraries(Test PUBLIC ${GTEST})
target_link_libraries(Test PUBLIC ${GTEST_MAIN})
