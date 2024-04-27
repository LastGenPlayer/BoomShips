//
// Created by Rain Verrev on 27.04.2024.
//

#include "Coord.h"

#include <iostream>

/*
Coord::Coord(int x, int y, bool isShip)
        : x(x),
          y(y),
          isHit(false),
          isShip(isShip) {}
*/
bool Coord::isNeighbour(Coord P1, Coord P2) {
    return std::max(std::abs(P1.x - P2.x), std::abs(P1.y - P2.y)) <= 1;
}

std::ostream &operator<<(std::ostream &os, const Coord &coord) {
    os << "x: " << coord.x << " y: " << coord.y << " isHit: " << coord.isHit << " isShip: " << coord.isShip;
    return os;
}

Coord::Coord(int x, int y, bool isShip):
    x(x),
    y(y),
    isHit(false),
    isShip(isShip){
}

/*
class Coord {
public:
    int x, y;
    bool isHit, isShip;

Coord::Coord(int x, int y, bool isShip)
    : x(x),
      y(y),
      isHit(false),
      isShip(isShip) {}

bool Coord::isNeighbour(Coord P1, Coord P2) {
    return std::max(std::abs(P1.x - P2.x), std::abs(P1.y - P2.y)) <= 1;
}

std::ostream &operator<<(std::ostream &os, const Coord &coord) {
    os << "x: " << coord.x << " y: " << coord.y << " isHit: " << coord.isHit << " isShip: " << coord.isShip;
    return os;
}

*/

