//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_SHIPS_H
#define BOOMSHIPS_SHIPS_H
#include <ostream>
#include <vector>
#include <string>

class Coord {
public:
    int x, y;
    bool isHit, isShip;

    Coord() = default;

    Coord(int x, int y, bool isShip)
        : x(x),
          y(y),
          isHit(false),
          isShip(isShip){
    }

    friend std::ostream &operator<<(std::ostream &os, const Coord &coord) {
        os << "x: " << coord.x << " y: " << coord.y << " isHit: " << coord.isHit << " isShip: " << coord.isShip;
        return os;
    }
};

class Ship {
public:
    int shipLength;
    std::vector<Coord> shipCoords;

    Ship(int x, int y, int ship_length, bool is_horizontal);
    Ship(std::string sisend);
    friend std::ostream & operator<<(std::ostream &os, const Ship &obj);
    bool onBoard();
    bool isSunk();
};


#endif //BOOMSHIPS_SHIPS_H
