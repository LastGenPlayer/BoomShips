//
// Created by Rain Verrev on 24.05.2024.
//

#include "AiPlayer.h"

template <typename T>
bool contains(const T* array, size_t size, const T& element) {
    for (size_t i = 0; i < size; ++i) {
        if (array[i] == element) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> AiPlayer::RandomGuess() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    int num1 = dis(gen);
    int num2 = dis(gen);
    while (playerBoard.coordid.at(num1*10+num2).isHit) {
        int temp = (num1 * 10 + num2 + 1) %100;
        num1 = temp/10;
        num2 = temp%10;
    }
    return std::pair<int, int>{num1, num2};
}

std::pair<int, int> AiPlayer::HuntingGuess() {
    std::pair<int, int> guess;
    if (targets.empty()) {
        isHunting = false;
        guess = RandomGuess();
    }
    else {
        guess = {targets[0]};
    }
    // guess = {x, y}
    if (playerBoard.coordid.at(guess.second*10 + guess.first).isShip) {
        std::pair<int, int> possibleTargets[4]{};

        if (!huntChecking) {
            if (targets.size() > 2) huntV = false;
            else huntH = false;
        }

        if (huntH) {
            possibleTargets[0] = std::pair<int, int>{guess.first + 1, guess.second};
            possibleTargets[1] = std::pair<int, int>{guess.first - 1, guess.second};
        }
        else {
            possibleTargets[0] = std::pair<int, int>{-1, -1};
            possibleTargets[1] = std::pair<int, int>{-1, -1};
        }
        if (huntV) {
            possibleTargets[2] = std::pair<int, int>{guess.first, guess.second + 1};
            possibleTargets[3] = std::pair<int, int>{guess.first, guess.second - 1};
        }
        else {
            possibleTargets[2] = std::pair<int, int>{-1, -1};
            possibleTargets[3] = std::pair<int, int>{-1, -1};
        }

        for (std::pair<int, int> target : possibleTargets) {
            if (0 <= target.first && target.first <= 9 &&
                0 <= target.second && target.second <= 9 &&
                playerBoard.isHittable(target) &&
                contains(possibleTargets, 4, target))
                {
                targets.push_back(target);
                }
        }
    }
    for (int i{}; i < targets.size(); i++) {
        if (!playerBoard.isHittable(targets[i])) {
            targets.erase(targets.cbegin()+i);
            i--;
        }
    }

    guess = targets[0];
    if (playerBoard.coordid.at(guess.second*10 + guess.first).isShip) huntChecking = false;
    if (targets.empty()) {
        isHunting = false;
        guess = RandomGuess();
    }
    return guess;
}




std::pair<int, int> AiPlayer::ProbabilityGuess() {
    std::pair<int, int> guess;
    int heatMap[10][10]{};

    std::vector<int> shipLength;
    for (auto& ship : playerBoard.Ships) {
        shipLength.push_back(ship.shipCoords.size());
    }
    std::set difShipLength(shipLength.begin(), shipLength.end());

    std::vector<Ship> possibleShips;
    std::map<int, std::vector<Ship>> possibleShipsOrganized;
    for (int len : difShipLength) {
        for (int i{}; i < 10; i++) {
            for (int j{}; j < 10; j++) {
                Ship hS(i, j, len, true);
                if (hS.onBoard() && playerBoard.isPlaceableAI(hS)) {
                    possibleShips.push_back(hS);
                    possibleShipsOrganized[len].push_back(hS);
                }
                if (len > 1) {
                    Ship vS(i, j, len, false);
                    if (vS.onBoard() && playerBoard.isPlaceableAI(vS)) {
                        possibleShips.push_back(vS);
                        possibleShipsOrganized[len].push_back(vS);
                    }
                }
            }
        }
    }
    std::cout << possibleShips.size();

    std::vector<std::pair<int, int>> invalidShipPositions;
    for (int i{}; i < possibleShips.size(); i++) {
        for (int j{i + 1}; j < possibleShips.size(); j++) {
            if (isIntersecting(possibleShips.at(i), possibleShips.at(j))) {
                invalidShipPositions.push_back(std::pair(i, j));
            }
        }
    }

    int possibleBoards{};
    while (possibleBoards < 10) {
        std::vector<Ship> candidateBoard;
        for (int ship : shipLength) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::vector<Ship> possibleShipPositions = possibleShipsOrganized[ship];
            std::uniform_int_distribution<> dis(0, possibleShipPositions.size() - 1);
            int index = dis(gen);
            candidateBoard.push_back(possibleShipPositions[index]);
        }
        for (int i{}; i < candidateBoard.size(); i++) {
            for (int j{i + 1}; j < candidateBoard.size(); j++) {
                if (isIntersecting(candidateBoard.at(i), candidateBoard.at(j))) {
                    candidateBoard = {};
                }
            }
        }
        for (const Ship& ship : candidateBoard) {
            for (Coord shipCoord : ship.shipCoords) {
                heatMap[shipCoord.x][shipCoord.y] += 1;
            }
        }
        possibleBoards += int(!candidateBoard.empty());
    }

    int i{}, j{};
    guess = {0, 0};
    for (; i < 10; i++) {
        for (; j < 10; j++) {
            if (heatMap[i][j] > heatMap[guess.first][guess.second]) {
                guess = {i, j};
            }
        }
    }

    return guess;
}

void AiPlayer::stageOnePrep(int amount) {
    for (int i{0}; i < amount; i++) {
        Board board{Board()};
        randomBoard(board);
        stageOneBoards.push_back(board);
    }
}


void AiPlayer::randomBoard(Board &board) {
    for (int lenght = 4; lenght > 0; lenght--) {
        for (int count = 5-lenght; count > 0;) {
            Ship ship = *new Ship(Game::randomCoord(), lenght);
            if (board.isPlaceable(ship)) {
                board.addShip(ship);
                count--;
            }
        }
    }
}

std::pair<int, int> AiPlayer::StageOneGuess() {
    int heatMap[10][10]{};
    bool add{true};
    for (int i{}; i < stageOneBoards.size(); i++) {
        add = true;
        Board& board = stageOneBoards[i];
        int tempMap[10][10]{};

        if (!checkVector(blacklist, i)){
            for (const auto &ship: board.Ships) {
                for (const auto &coord: ship.shipCoords) {
                    int coordI{coord.y * 10 + coord.x};
                    if (playerBoard.coordid.at(coordI).isHit && !playerBoard.coordid.at(coordI).isShip) {
                        add = false;
                    }
                    else if (!playerBoard.coordid.at(coordI).isHit) {
                        tempMap[coord.y][coord.x] += 1;
                    }
                }
            }
            if (add) {
                for (int j{}; j < 100; j++){
                    heatMap[j/10][j%10] += tempMap[j/10][j%10];
                }
            }
            else {
                blacklist.push_back(i);
            }
        }
    }

    std::pair<int, int>guess = {0, 0};
    for (int y{}; y < 10; y++) {
        for (int x{}; x < 10; x++) {
            if (heatMap[y][x] > heatMap[guess.second][guess.first]) {
                guess = {x, y};
            }
        }
    }

    return guess;
}

bool AiPlayer::checkVector(std::vector<int> list, int j) {
    for (const auto &item: list) {
        if (j == item) return true;
    }
    return false;
}







