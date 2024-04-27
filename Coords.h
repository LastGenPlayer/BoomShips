//
// Created by Rain Verrev on 27.04.2024.
//

#ifndef COORDS_H
#define COORDS_H
#include <iostream>

class Coord {
public:
    int x, y;
    bool isHit, isShip;

    Coord();
    Coord(int x, int y, bool isShip);
    static bool isNeighbour(Coord P1, Coord P2);
    friend std::ostream &operator<<(std::ostream &os, const Coord &coord);
};

#endif //COORDS_H
