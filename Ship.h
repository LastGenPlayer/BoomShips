//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_SHIPS_H
#define BOOMSHIPS_SHIPS_H
#include <ostream>

class Coord {
public:
    int x, y;
    bool isHit;

    Coord() = default;

    Coord(int x, int y)
        : x(x),
          y(y),
          isHit(false) {
    }
};

class Ship {
    int shipLength;
    std::vector<Coord> shipCoords;
public:
    Ship(int x, int y, int ship_length, bool is_horizontal);
    friend std::ostream & operator<<(std::ostream &os, const Ship &obj);
};


#endif //BOOMSHIPS_SHIPS_H
