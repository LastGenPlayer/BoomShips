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


Game::Game() : board1(Board()),
    board2(Board()) {
    std::string sisend;
    for (;;) {
        std::cout << "Kas soovite automaatselt genereeritud lauda või ise luua (a/i)?\n";
        std::cin >> sisend;
        if (sisend == "i") {
            selfBoard(sisend);
            break;
        }
        if (sisend == "a") {
            randomBoard();
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
                if (Board::isPlaceable(ship, board1.Ships)) {
                    board1.addShip(ship);
                    count--;
                    std::cout << board1;
                }
            }
        }
    }
}

void Game::randomBoard() {
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            Ship ship = *new Ship(randomCoord(), lenght);
            if (Board::isPlaceable(ship, board1.Ships)) {
                board1.addShip(ship);
                count--;
            }
        }
    }
    std::cout << board1;
}

void Game::playGame() {

}

void Game::guessSpot(std::string koht) {
    std::string tahed{"ABCDEFGHIJ"};
    std::string num{"1234567890"};
    int x = static_cast<int>(tahed.find(koht.at(0)));
    int y = static_cast<int>(num.find(koht.at(1)));
}


