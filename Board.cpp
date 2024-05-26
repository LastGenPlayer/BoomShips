//
// Created by krist on 24/04/2024.
//

#include "Board.h"
#include "Ship.h"


/**
 * laua konstruktor. Loob vektori 100 koordinaadiga (10x10)
 * miks me nii tegime...
 */
Board::Board() : visible(true) {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            coordid.push_back(Coord(x, y, false));
        }
    }
}

/**
 * Laua loomine koos laeva asukohtadega
 * @param ships
 * @param visible
 */
Board::Board(std::vector<Ship> &ships, bool visible) : Ships(ships), visible(visible) {
    if (coordid.empty()) {
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                coordid.push_back(Coord(x, y, false));
            }
        }
    }
    for (Ship ship : ships) {
        for (Coord coord : ship.shipCoords) {
            coordid[coord.y*10 + coord.x] = coord;
        }
    }
}

/**
 * toString
 * @param os
 * @param board
 * @return
 */
std::ostream &operator<<(std::ostream &os, const Board &board) {
    int i{0};

    os << "   A B C D E F G H I J";
    for (Coord asi : board.coordid) {

        if (i%10 == 0 && i/10 < 10){
            os << '\n' << ((i/10)+1)%10 << "  ";
        }

        if (asi.isShip && !asi.isHit && board.visible) {
            os << "# ";
        }
        else if (asi.isShip && asi.isHit) {
            os << "@ ";
        }
        else if (!asi.isShip && asi.isHit) {
            os << "* ";
        }
        else {
            os << ". ";
        }
        i++;
    }

    os << '\n';
    /*
    for (Coord asi : board.coordid) {
        os << asi << '\n';
    }
     */
    return os;
}

/**
 * kaks kõrvuti lauda "toString" (tegelt prindib funktsioonis juba)
 * @param board1
 * @param board2
 */
void Board::coutToString(Board& board1, Board& board2) {
    bool teine = true;
    Board temp{board1};

    std::cout << "   A B C D E F G H I J      A B C D E F G H I J";
    for (int i = 0; i <= 100; i++) {
        if (i%10 == 0){
            if (!teine && i >= 10) {
                std::cout << "  ";
                temp = board2;
                i -= 10;
            }
            if (teine) {
                temp = board1;
                std::cout << '\n';
            }
            teine = !teine;
            if (!teine && i == 100) break;
            std::cout << ((i/10)+1)%10 << "  ";
        }

        Coord temp2{temp.coordid[i]};
        if (temp2.isShip && !temp2.isHit && temp.visible) {
            std::cout << "# ";
        }
        else if (temp2.isShip && temp2.isHit) {
            std::cout << "@ ";
        }
        else if (!temp2.isShip && temp2.isHit) {
            std::cout << "* ";
        }
        else {
            std::cout << ". ";
        }
    }
    std::cout << '\n';
}

/**
 * kontroll, kas laeva saab asetada lauale
 * @param ship
 * @return
 */
bool Board::isPlaceable(Ship ship) {
    if (!ship.onBoard()) {
        return false;
    }
    for (const Ship& boat : Ships) {
        for (Coord boatCoord : boat.shipCoords) {
            for (Coord shipCoord : ship.shipCoords) {
                if (Coord::isNeighbour(boatCoord, shipCoord)) {
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * AI pakkumise jaoks kontroll
 * @param ship
 * @return
 */
bool Board::isPlaceableAI(Ship ship) {
    for (Coord shipCoord : ship.shipCoords) {
        if (coordid[shipCoord.y*10 + shipCoord.x].isHit) {
            return false;
        }
    }
    return true;
}

/**
 * lisab laeva lauale
 * @param ship
 */
void Board::addShip(Ship ship) {
    this->Ships.push_back(ship);
    for (Coord coord : ship.shipCoords) {
        coordid[coord.y*10 + coord.x] = coord;
    }
}

std::pair<int, int> Board::guessSpot(std::string sisend) {
    std::string tahed{"ABCDEFGHIJ"};
    std::string num{"1234567890"};
    std::pair<int, int> guess;
    int x = (tahed.find(sisend.at(0)) != -1) ? static_cast<int>(tahed.find(sisend.at(0))) : 9999;
    int y = (num.find(sisend.at(1)) != -1) ? static_cast<int>(num.find(sisend.at(1))) : 9999;
    guess.first = x;
    guess.second = y;

    return guess;
}

bool Board::isHittable(std::pair<int, int> guess) {
    return !(&(this->coordid)[guess.second*10 + guess.first])->isHit;
}

void Board::FIREINTHEHOLE(std::pair<int, int> guess) {
    FIREINTHEHOLE(guess.first, guess.second);
}

void Board::FIREINTHEHOLE(int x, int y) {
    Coord* coord = (&(this->coordid)[y * 10 + x]);
    coord->isHit = true;

    if (coord->isHit && coord->isShip) {
        for (int i = -1; i < 2; i+=2) {
            for (int j = -1; j < 2; j+=2) {
                if (x+i >= 0 && x+i <= 9 && y+j >= 0 && y+j <= 9)
                FIREINTHEHOLE(x+i, y+j);
            }
        }
    }
    for (Ship& ship : this->Ships) {
        for (Coord& coord : ship.shipCoords) {
            if (x == coord.x && y == coord.y) {
                coord.isHit = true;
                break;
            }
        }
    }
}

void Board::sinkShip(Board& board, Ship ship) {
    for (Coord coord : ship.shipCoords) {
        for (Coord& boardCoord : board.coordid) {
            if (Coord::isNeighbour(coord, boardCoord)) {
                boardCoord.isHit = true;
            }
        }
    }
}


