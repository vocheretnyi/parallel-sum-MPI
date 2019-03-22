cmake_minimum_required(VERSION 3.13)
project(MPI)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

add_executable(MPI main.cpp)
