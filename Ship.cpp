//
// Created by krist on 24/04/2024.
//

#include "Ship.h"

Ship::Ship(int x, int y, int ship_length, bool is_horizontal) : shipLength(ship_length) {
    if (is_horizontal) {
        for (int i = 0; i < ship_length; i++) {
            shipCoords.push_back(Coord(x + i, y, true));
        }
    }
    else {
        for (int i = 0; i < ship_length; i++) {
            shipCoords.push_back(Coord(x, y + i, true));
        }
    }
}

std::ostream & operator<<(std::ostream &os, const Ship &obj) {
    os << obj.shipLength << '\n';
    for (auto coord: obj.shipCoords) {
        os << coord.x << ' '
           << coord.y << ' '
           << std::boolalpha
           << coord.isHit << ' '
           << coord.isShip << '\n';
    }
    return os;
}

bool Ship::isSunk() {
    for (int i = 0; i < this->shipLength; i++) {
        if (!this->shipCoords.at(i).isHit) {
            return false;
        }
    }
    return true;
}

