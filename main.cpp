#include <iostream>
#include "Ship.h"
#include "Board.h"
#include "Game.h"


int main() {
    /*
    Ship S(1,1,3,false);
    Ship S2(1,3,3,true);
    std::cout << S;

    std::vector<Ship> ships{S, S2};
    Board a(ships, true);
    std::cout << a << '\n';
    */

    Game mang = *new Game();
    mang.playGame();

    // Ship S1(1,1,3,true);
    // Ship S2(2,2,3,true);
    // std::cout << isIntersecting(S1, S2);
}
