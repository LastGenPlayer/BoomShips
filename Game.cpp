//
// Created by krist on 27.04.2024.
//

#include <iostream>
#include <random>
#include <map>
#include "Game.h"
#include "Ship.h"
#include "AiPlayer.h"

std::string Game::randomCoord() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int num1 = dis(gen);
    int num2 = dis(gen);
    int num3 = dis(gen);
    std::map<int, std::string> firstCoord={
            {1, "A",},
            {2, "B",},
            {3, "C",},
            {4, "D",},
            {5, "E",},
            {6, "F",},
            {7, "G",},
            {8, "H",},
            {9, "I",},
            {10, "J",}
    };
    std::map<int, std::string> horizontalOrVertical={
            {0, "h",},
            {1, "v",}
    };
    return firstCoord[num1] + std::to_string(num2 - 1) + horizontalOrVertical[num3 % 2];
}


Game::Game() : board1(Board()),
    board2(Board())
    {
    std::string sisend;
    randomBoard(board2);
    for (;;) {
        std::cout << "Kas soovite automaatselt genereeritud lauda või ise luua (a/i)?\n";
        std::cout << "Beta note: Soovitame automaatse panna kuna vastase pakkumine pole implementeeritud\n";
        std::cin >> sisend;
        if (sisend == "i") {
            selfBoard(sisend);
            break;
        }
        if (sisend == "a") {
            randomBoard(board1);
            break;
        }
    }
}

void Game::selfBoard(std::string &sisend) {
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            std::cout << "Sisesta koordinaat " << lenght << "x1 laeva paigutamiseks (täht, number ja kas horisontaalselt (h) või vertikaalselt (v) nt A2h)\n";
            std::cin >>  sisend;
            if (sisend.size() == 3) {
                Ship ship = *new Ship(sisend, lenght);
                if (board1.isPlaceable(ship)) {
                    board1.addShip(ship);
                    count--;
                    std::cout << board1;
                }
            }
        }
    }
}

void Game::randomBoard(Board &board) {
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            Ship ship = *new Ship(randomCoord(), lenght);
            if (board.isPlaceable(ship)) {
                board.addShip(ship);
                count--;
            }
        }
    }
}

void Game::playGame() {
    this->board2guess = Board(board2.Ships, false);
    bool gamerMoment{true};
    AiPlayer AI(board1);
    while (gamerMoment) {
        while(true) {
            bool firstShot{true};
            std::cout << board2 << '\n';
            //std::cout << board2guess << '\n';
            Board::coutToString(board2guess, board1);
            std::string sisend;
            std::cout << "Paku ruut (nt. A3):\n";
            std::cin >> sisend;

            if (sisend.size() == 2) {
                Coord pakkumine = Coord(sisend);
                std::pair<int, int> AiGuess{};
                if(pakkumine.isValid()){
                    std::pair<int, int> guess = Board::guessSpot(sisend);
                    if (board2.isHittable(guess)) {
                        board2.FIREINTHEHOLE(guess);
                        board2guess.FIREINTHEHOLE(guess);

                        if (!board2.coordid.at(guess.second*10+guess.first).isShip) {
                            while (board1.coordid.at(AiGuess.second*10+AiGuess.first).isShip || firstShot) {
                                firstShot = false;
                                if (AI.isHunting) {
                                    AiGuess = AI.HuntingGuess();
                                }
                                else if (AI.stageOne) {
                                    AiGuess = AI.StageOneGuess();
                                }
                                else {
                                    AiGuess = AI.ProbabilityGuess();
                                }
                                //std::cout << AiGuess.second << AiGuess.first << '\n';
                                board1.FIREINTHEHOLE(AiGuess);
                                AI.playerBoard.FIREINTHEHOLE(AiGuess);
                                allSunk(AI.playerBoard);
                                if (board1.coordid.at(AiGuess.second*10+AiGuess.first).isShip) {
                                    if (!AI.isHunting) AI.targets.push_back(AiGuess);
                                    AI.isHunting = true;
                                }
                            }
                        }
                    }
                    if (AI.stageOneBoards.size() < 4000) {
                        AI.stageOnePrep(250);
                    }

                    if (allSunk(board1)) {
                        std::cout << "Teie kaotasite\n";
                        gamerMoment = false;
                        break;
                    }
                    if (allSunk(board2)) {
                        std::cout << "Teie võitsite\n";
                        gamerMoment = false;
                        break;
                    }
                    allSunk(board2guess);
                }
            }
        }
    }
    std::cout << "Mäng läbi!";
}

bool Game::allSunk(Board &board) {
    int board2ships{0};
    for (Ship ship : board.Ships) {
        if (ship.isSunk()) {
            Board::sinkShip(board, ship);
            board2ships++;
        }
    }
    if (board2ships == 10) {
        return true;
    }
    return false;
}



/*
void Game::keepGuessing(std::pair<int, int>& AiGuess, AiPlayer& AI) {
    if (AI.stageOne) {
        AiGuess = AI.StageOneGuess();
    }
    else if (AI.isHunting) {
        AiGuess = AI.HuntingGuess();
    }
    else {
        AiGuess = AI.ProbabilityGuess();
    }
    std::cout << AiGuess.first << AiGuess.second << '\n';
    board1.FIREINTHEHOLE(AiGuess);
    AI.playerBoard.FIREINTHEHOLE(AiGuess);
    if (board1.coordid.at(AiGuess.first*10+AiGuess.second).isShip) {
        keepGuessing(AiGuess, AI);
    }
}*/


