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
    void selfBoard(std::string &sisend);
    void playGame();
    void randomBoard();
    static std::string randomCoord();
    void guessSpot(std::string koht);

};


#endif //BOOMSHIPS_GAME_H
