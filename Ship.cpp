//
// Created by krist on 24/04/2024.
//

#include "Ship.h"
#include "Coord.h"
#include <iostream>
#include <string>
#include <unordered_set>

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

/**
 * Loob laeva objekti elemendid
 * @param x - x koordinaat
 * @param y y koordinaat
 * @param ship_length - laeva pikkus (läheb katki)
 * @param is_horizontal - kas on horisontaalne või mitte (ehk vertikaalne)
 */
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

/**
 * toString
 * @param os
 * @param obj
 * @return
 */
std::ostream & operator<<(std::ostream &os, const Ship &obj) {
    os << obj.shipLength << '\n';
    for (Coord coord: obj.shipCoords) {
        os << coord << '\n';
    }
    return os;
}

/**
 * kontrollib, kas laev on põhjas (kõik laeva koordinaadid on pihta saanud)
 * @return
 */
bool Ship::isSunk() {
    for (Coord coord : this->shipCoords) {
        //std::cout << this->shipCoords[i];
        if (!coord.isHit) {
            return false;
        }
    }
    return true;
}

/**
 * kontroll, kas laev on laua peal
 * @return
 */
bool Ship::onBoard() {
    for (Coord P: this->shipCoords) {
        if ((P.x == 10) || (P.y == 10)) {
            return false;
        }
    }
    return true;
}

/**
 * kontroll, kas kaks laeva on üksteisest piisavalt kaugel
 * @param S1 - laev 1
 * @param S2 - laev 2
 * @return
 */
bool isIntersecting(Ship S1, Ship S2) {
    for (auto& coord1 : S1.shipCoords) {
        for (auto& coord2 : S2.shipCoords) {
            if (Coord::isNeighbour(coord1, coord2)) {
                return true;
            }
        }
    }
    return false;
}

