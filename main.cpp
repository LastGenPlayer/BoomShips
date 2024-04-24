#include <iostream>
#include "Ship.h"

struct Test {
    int x;
};

int main() {
    Ship S(1,1,3,false);

    std::cout << S;
}
