cmake_minimum_required(VERSION 3.27)
project(BoomShips)

set(CMAKE_CXX_STANDARD 20)

add_executable(BoomShips main.cpp
        ships.cpp
        ships.h
        board.cpp
        board.h)
