//
// Created by krist on 27.04.2024.
//

#ifndef BOOMSHIPS_GAME_H
#define BOOMSHIPS_GAME_H

#include "Board.h"

class Game {
public:
    Board board1;
    Board board2;
    Board board2guess;

    Game();
    void selfBoard(std::string &sisend);
    void playGame();
    static void randomBoard(Board&);
    static std::string randomCoord();

};


#endif //BOOMSHIPS_GAME_H
