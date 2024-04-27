//
// Created by krist on 27.04.2024.
//

#include <iostream>
#include <cmath>
#include "Game.h"
#include "Ship.h"

Game::Game() : board1(Board()),
    board2(Board()) {
    // AI generated board here

    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            std::string sisend;
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

void Game::playGame() {

}
