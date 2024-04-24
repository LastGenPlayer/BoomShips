//
// Created by krist on 24/04/2024.
//

#include "Board.h"

Board::Board(const std::vector<Ship> &ships, bool visible) : Ships(ships), visible(visible) {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; ++x) {
            coordid.push_back(Coord(x, y, false));
        }
    }
    for (Ship ship : ships) {
        for (Coord coord : ship.shipCoords) {
            coordid.erase(coordid.begin() + coord.y*10 + coord.x);
            coordid.insert(coordid.begin() + coord.y*10 + coord.x, coord);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    os << "  A B C D E F G I J K\n1 ";
    int i{0};
    if (board.visible) {
        for (Coord asi : board.coordid) {
            if (asi.isShip) {
                os << "@ ";
            }
            else {
                os << ". ";
            }
            i++;
            if (i%10 == 0 && i/10 < 10){
                os << '\n' << ((i/10)+1);
                if ((i/10)+1 != 10) {
                    os << " ";
                }
            }
        }
    }

    /**
    for (Coord asi : board.coordid) {
        os << asi << '\n';
    }
    return os;
     **/
}
