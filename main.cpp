#include <iostream>
#include "Ship.h"
#include "Board.h"


int main() {
    Ship S(1,1,3,false);
    Ship S2(1,3,3,true);
    std::cout << S;

    std::vector<Ship> ships{S, S2};
    Board a(ships, true);
    std::cout << a << '\n';

    std::cout << std::endl;

    Coord P1(3, 4, false);
    Coord P2(3, 4, false);
    Coord P3(3, 4, false);


}
