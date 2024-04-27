//
// Created by krist on 24/04/2024.
//

#include "Ship.h"
#include "Coord.h"
#include <iostream>
#include <string>

Ship::Ship(int x, int y, int ship_length, bool is_horizontal) : shipLength(ship_length) {
    shipMaker(x, y, ship_length, is_horizontal);
}


Ship::Ship(std::string sisend, int lenght) {
    std::string tahed{"ABCDEFGHIJ"};
    std::string num{"1234567890"};
    int x = (tahed.find(sisend.at(0)) != -1) ? static_cast<int>(tahed.find(sisend.at(0))) : 9999;
    int y = (num.find(sisend.at(1)) != -1) ? static_cast<int>(num.find(sisend.at(1))) : 9999;
    //int y = (int) sisend.at(1) - 49; // A6h
    bool hori = (sisend.at(2) == 'h');
    shipMaker(x, y, lenght, hori);
}


void Ship::shipMaker(int x, int y, int ship_length, bool is_horizontal) {
    if (is_horizontal) {
        for (int i = 0; i < ship_length; i++) {
            Coord coord = Coord(x + i, y, true);
            shipCoords.push_back(coord);
        }
    } else {
        for (int i = 0; i < ship_length; i++) {
            Coord coord = Coord(x, y + i, true);
            shipCoords.push_back(coord);
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
        std::cout << this->shipCoords[i];
        if (this->shipCoords[i].isHit) {
            return true;
        }
    }
    return false;
}

bool Ship::onBoard() {
    for (Coord P: this->shipCoords) {
        if ((P.x == 10) || (P.y == 10)) {
            return false;
        }
    }
    return true;
}
