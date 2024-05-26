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


    std::vector<int> asi;
    asi.push_back(1);
    asi.push_back(2);
    asi.push_back(3);

    std::cout << asi[0];
    std::cout << asi[1];
    std::cout << asi[2] << '\n';

    asi.erase(asi.cbegin()+1, asi.cend()-1);
    std::cout << asi.size()<< '\n';
    std::cout << asi[0];
    std::cout << asi[1];
    std::cout << asi[2] << '\n';
*/
    Game mang = *new Game();
    mang.playGame();

    // Ship S1(1,1,3,true);
    // Ship S2(2,2,3,true);
    // std::cout << isIntersecting(S1, S2);
}
