//
// Created by krist on 24/04/2024.
//

#include "Board.h"
#include "Ship.h"

Board::Board() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            coordid.push_back(Coord(x, y, false));
        }
    }
}

Board::Board(std::vector<Ship> &ships, bool visible) : Ships(ships), visible(visible) {
    if (coordid.empty()) {
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                coordid.push_back(Coord(x, y, false));
            }
        }
    }
    for (Ship ship : ships) {
        for (Coord coord : ship.shipCoords) {
            coordid[coord.y*10 + coord.x] = coord;
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    int i{0};
    if (!board.visible) {
        os << "   A B C D E F G H I J\n1  ";
        for (Coord asi : board.coordid) {
            if (asi.isShip) {
                os << "@ ";
            }
            else {
                os << ". ";
            }
            i++;
            if (i%10 == 0 && i/10 < 10){
                os << '\n' << ((i/10)+1)%10 << "  ";
            }
        }
    }
    os << '\n';
    /*
    for (Coord asi : board.coordid) {
        os << asi << '\n';
    }
     */
    return os;
}

bool Board::isPlaceable(Ship ship, const std::vector<Ship>& boats) {
    if (!ship.onBoard()) {
        return false;
    }
    for (const Ship& boat : boats) {
        for (Coord boatCoord : boat.shipCoords) {
            for (Coord shipCoord : ship.shipCoords) {
                if (Coord::isNeighbour(boatCoord, shipCoord)) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::addShip(Ship ship) {
    this->Ships.push_back(ship);
    for (Coord coord : ship.shipCoords) {
        coordid[coord.y*10 + coord.x] = coord;
    }
}


