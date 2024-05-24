//
// Created by Rain Verrev on 27.04.2024.
//

#ifndef COORD_H
#define COORD_H
#include <iostream>

class Coord {
public:
    int x, y;
    bool isHit, isShip;

    Coord(int x, int y, bool isShip);
    Coord(std::string);
    bool isValid();
    static bool isNeighbour(Coord P1, Coord P2);
    friend std::ostream &operator<<(std::ostream &os, const Coord &coord);
};

#endif //COORDS_H
