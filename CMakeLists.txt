cmake_minimum_required(VERSION 3.29)
project(sandpile-simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(sandpile-simulator
    main.cpp
        heap.h
        heap.cpp
        bmp_writer.h
        bmp_writer.cpp)
