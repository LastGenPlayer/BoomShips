//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_BOARD_H
#define BOOMSHIPS_BOARD_H

#include <ostream>
#include "Ship.h"


class Board {
public:
    std::vector<Ship> Ships;
    std::vector<Coord> coordid;
    bool visible;


    Board();
    Board(std::vector<Ship> &ships, bool visible);
    void addShip(Ship);
    static void coutToString(Board&, Board&);
    bool isPlaceable(Ship);
    bool isPlaceableAI(Ship);
    static std::pair<int, int> guessSpot(std::string);
    bool isHittable(std::pair<int, int>);
    void FIREINTHEHOLE(std::pair<int, int>);
    void FIREINTHEHOLE(int, int);

    static void sinkShip(Board&, Ship);
    friend std::ostream &operator<<(std::ostream &os, const Board &board);
};


#endif //BOOMSHIPS_BOARD_H
