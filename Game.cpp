//
// Created by krist on 27.04.2024.
//

#include <iostream>
#include <random>
#include <map>
#include "Game.h"
#include "Ship.h"

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


Game::Game() : board1(new Board()),
    board2(new Board())
    {
    std::string sisend;
    randomBoard(board2);
    for (;;) {
        std::cout << "Kas soovite automaatselt genereeritud lauda või ise luua (a/i)?\n";
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
                if (Board::isPlaceable(ship, board1->Ships)) {
                    board1->addShip(ship);
                    count--;
                    std::cout << board1;
                }
            }
        }
    }
}

void Game::randomBoard(Board* board) {
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            Ship ship = *new Ship(randomCoord(), lenght);
            if (Board::isPlaceable(ship, (*board).Ships)) {
                (*board).addShip(ship);
                count--;
            }
        }
    }
}

void Game::playGame() {
    this->board2guess = new Board(board2->Ships, false);
    bool gamerMoment{true};
    while (gamerMoment) {
        while(true) {
            std::cout << *board2guess << '\n';
            std::cout << *board2;
            std::string sisend;
            std::cout << "Paku auku:\n";
            std::cin >> sisend;

            std::pair<int, int> guess = Board::guessSpot(sisend);

            if (sisend.length() == 2 && board2->isHittable(guess)) {
                board2->FIREINTHEHOLE(guess);
                board2guess->FIREINTHEHOLE(guess);
            }
            else {
                break;
            }

            int board2ships{0};
            for (Ship ship : board2->Ships) {
                std::cout << ship << '\n';
                if (!ship.isSunk()) {

                }
                else {
                    Board::sinkShip(*board2, ship);
                    Board::sinkShip(*board2guess, ship);
                    board2ships++;
                }
            }
            if (board2ships == 10) {
                gamerMoment = false;
                break;
            }
        }
    }
    std::cout << "Mäng läbi!";
}





