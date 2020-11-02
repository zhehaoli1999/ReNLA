cmake_minimum_required(VERSION 3.16)
project(Codes)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
add_executable(Chap1 src/Matrix.cpp include/Matrix.h src/LinearSolver.cpp include/LinearSolver.h src/Vec.cpp include/Vec.h src/chap1.cpp src/Timer.cpp include/Timer.h)
add_executable(Chap2 src/Matrix.cpp include/Matrix.h src/LinearSolver.cpp include/LinearSolver.h src/Vec.cpp include/Vec.h src/chap2.cpp src/Timer.cpp include/Timer.h)

find_library(GTEST libgtest.a  /usr/local/lib/)
find_library(GTEST_MAIN libgtest_main.a  /usr/local/lib/)
find_library(GMOCK libgmock.a  /usr/local/lib/)
find_library(GMOCK_MAIN libgmock_main.a  /usr/local/lib/)

add_executable(Test include/Vec.h src/Vec.cpp test/VecTest.cpp
        include/Matrix.h src/Matrix.cpp test/MatrixTest.cpp)

target_link_libraries(Test PUBLIC ${GTEST})
target_link_libraries(Test PUBLIC ${GTEST_MAIN})
#target_link_libraries(Test PUBLIC ${GMOCK})
#target_link_libraries(Test PUBLIC ${GMOCK_MAIN})
