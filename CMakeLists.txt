cmake_minimum_required(VERSION 3.6)
project(dsalglib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tests.h include/heapsort.h include/insertionsort.h include/mergesort.h include/shellsort.h include/selectionsort.h include/matrix.h include/kmpsearch.h include/graph.h timepass.h)
add_executable(dsalglib ${SOURCE_FILES})