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

    Game();
    void playGame();
};


#endif //BOOMSHIPS_GAME_H
