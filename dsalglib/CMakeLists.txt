cmake_minimum_required(VERSION 3.6)
project(dsalglib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/alginc.h
    include/array.h
    include/avltree.h
    include/binarysearch.h
    include/bstree.h
    include/bubblesort.h
    include/graph.h
    include/heap.h
    include/heapsort.h
    include/insertionsort.h
    include/kmpsearch.h
    include/linklist.h
    include/matrix.h
    include/mergesort.h
    include/queue.h
    include/quicksort.h
    include/search.h
    include/selectionsort.h
    include/shellsort.h
    include/sort.h
    include/splaytree.h
    include/stack.h
    include/tree.h
    dsalglib.h
    main.cpp
    sample.h
    tests.h
    timepass.h include/hashmap.cpp include/hashmap.h)

add_executable(dsalglib ${SOURCE_FILES})