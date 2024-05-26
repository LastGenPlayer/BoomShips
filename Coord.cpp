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
/**
 * Kontrollib, kas kaks koordinaati on naabrid (küljed või nurgad puutuvad)
 * @param P1
 * @param P2
 * @return
 */
bool Coord::isNeighbour(Coord P1, Coord P2) {
    return std::max(std::abs(P1.x - P2.x), std::abs(P1.y - P2.y)) <= 1;
}

/**
 * toString
 * @param os
 * @param coord
 * @return
 */
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

/**
 * koordinaadi konstruktor kasutades string sisendit
 * @param sis - string kujul koordinaat (nt A2)
 */
Coord::Coord(std::string sis) : isHit(false), isShip(false) {
    std::string tahed{"ABCDEFGHIJ"};
    std::string num{"1234567890"};
    int xa = (tahed.find(sis.at(0)) != -1) ? (int)(tahed.find(sis.at(0))) : -1;
    int ya = (num.find(sis.at(1)) != -1) ? (int)(num.find(sis.at(1))) : -1;
    this->x = xa;
    this->y = ya;
}

/**
 * kontroll, kas koordinaat on valiidne
 * @return
 */
bool Coord::isValid() {
    return (x >= 0 && x < 10 && y >= 0 && y < 10);
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

