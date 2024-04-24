//
// Created by krist on 24/04/2024.
//

#ifndef BOOMSHIPS_SHIPS_H
#define BOOMSHIPS_SHIPS_H

struct Coord {
    int x, y;
    bool isHit;
};

class Ships {
    int shipLength;
    Coord shipCoords[];
public:
    explicit Ships(int x, int y, int ship_length, bool is_horizontal)
        : shipLength(ship_length) {
        Coord shipCoords[shipLength];
        if (is_horizontal) {
            for (int i = 0; i < ship_length; i++) {
                shipCoords[i] = Coord(x + i, y, false);
            }
        }
    }
};


#endif //BOOMSHIPS_SHIPS_H
