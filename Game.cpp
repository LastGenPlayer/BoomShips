//
// Created by krist on 27.04.2024.
//

#include <iostream>
#include <cmath>
#include "Game.h"
#include "Ship.h"

Game::Game() : board1(Board()),
    board2(Board()) {
    std::cout << "Game sees";
    // AI generated board here

    std::vector<Ship> boatsNhoes;
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0; count--) {
            std::string sisend;
            std::cout << "Sisesta koordinaat " << lenght << "x1 laeva paigutamiseks (täht, number ja kas horisontaalselt (h) või vertikaalselt (v) nt A2h)\n";
            std::cin >>  sisend;
            Ship ship = *new Ship(sisend, lenght);
            if (ship.onBoard() && Board::isPlaceable(ship, boatsNhoes)) {
                boatsNhoes.push_back(ship);
            }
        }
    }

    board1 = Board(boatsNhoes, true);
    board2 = Board();
}

void Game::playGame() {

}
