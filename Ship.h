//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_SHIPS_H
#define BOOMSHIPS_SHIPS_H
#include "Coord.h"
#include <ostream>
#include <vector>
#include <string>

class Ship {
public:
    int shipLength;
    std::vector<Coord> shipCoords;

    Ship(int x, int y, int ship_length, bool is_horizontal);
    Ship(std::string sisend, int lenght);
    void shipMaker(int x, int y, int ship_length, bool is_horizontal);
    friend std::ostream & operator<<(std::ostream &os, const Ship &obj);
    bool onBoard();
    bool isSunk();
    bool isHit() const;
    friend bool isIntersecting(Ship S1, Ship S2);
};


#endif //BOOMSHIPS_SHIPS_H
