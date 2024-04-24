//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_SHIPS_H
#define BOOMSHIPS_SHIPS_H
#include <ostream>

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
};

class Ship {
    int shipLength;
    std::vector<Coord> shipCoords;
public:
    Ship(int x, int y, int ship_length, bool is_horizontal);
    friend std::ostream & operator<<(std::ostream &os, const Ship &obj);
    bool isSunk();
};


#endif //BOOMSHIPS_SHIPS_H
