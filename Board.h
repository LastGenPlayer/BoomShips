//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_BOARD_H
#define BOOMSHIPS_BOARD_H

#include <ostream>
#include "Ship.h"



class Board {

    std::vector<Ship> Ships;
    std::vector<Coord> coordid;
    bool visible;

public:
    Board();
    Board(std::vector<Ship> &ships, bool visible);
    static bool isPlaceable(Ship ship, const std::vector<Ship>& boats);

    friend std::ostream &operator<<(std::ostream &os, const Board &board);
};


#endif //BOOMSHIPS_BOARD_H
