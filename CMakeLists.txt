cmake_minimum_required(VERSION 3.27)
project(BoomShips)

set(CMAKE_CXX_STANDARD 20)

add_executable(BoomShips main.cpp
        Ship.cpp
        Ship.h
        Board.cpp
        Board.h
        Game.cpp
        Game.h
        Coord.cpp
        Coord.h
        AiPlayer.cpp
        AiPlayer.h
)
