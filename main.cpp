#include <iostream>
#include "Ship.h"

struct Test {
    int x;
};

int main() {
    Ship S(1,1,8,true);
    std::cout << std::boolalpha << S.isSunk() << std::endl;
    std::cout << S;
}
