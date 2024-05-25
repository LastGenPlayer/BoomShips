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
    return std::pair<int, int>{num1, num2};
}

std::pair<int, int> AiPlayer::HuntingGuess() {
    std::pair<int, int> guess;
    if (!targets.empty()) {
        guess = RandomGuess();
    }
    else {
        guess = std::pair<int, int>{targets.back().first, targets.back().second};
    }
    if (!currenGame.board1.isHittable(guess)) {
        std::pair<int, int> possibleTargets[] {
            std::pair<int, int>{guess.first + 1, guess.second},
            std::pair<int, int>{guess.first - 1, guess.second},
            std::pair<int, int>{guess.first, guess.second + 1},
            std::pair<int, int>{guess.first, guess.second - 1}
        };
        for (std::pair<int, int> target : possibleTargets) {
            if (0 <= target.first && target.first <= 9 &&
                0 <= target.second && target.second <= 9 &&
                currenGame.board1.isHittable(target) &&
                contains(possibleTargets, 4, target))
                {
                targets.push_back(target);
                }
        }
    }
    return guess;
}

std::pair<int, int> AiPlayer::ProbabilityGuess() {
    Board playerBoard = currenGame.board1;
    std::pair<int, int> guess;
    int heatMap[10][10]{};

    std::vector<int> shipLength;
    for (auto& ship : playerBoard.Ships) {
        shipLength.push_back(ship.shipLength);
    }
    std::set difShipLength(shipLength.begin(), shipLength.end());

    std::vector<Ship> possibleShips;
    std::map<int, std::vector<Ship>> possibleShipsOrganized;
    for (int len : difShipLength) {
        for (int i{}; i < 10; i++) {
            for (int j{}; j < 10; j++) {
                Ship hS(i, j, len, true);
                Ship vS(i, j, len, false);
                if (playerBoard.isPlaceableAI(hS)) {
                    possibleShips.push_back(hS);
                    possibleShipsOrganized[len].push_back(hS);
                }
                if (playerBoard.isPlaceableAI(vS)) {
                    possibleShips.push_back(vS);
                    possibleShipsOrganized[len].push_back(vS);
                }
            }
        }
    }

    std::vector<std::pair<Ship, Ship>> invalidShipPositions;
    for (int i{}; i < possibleShips.size(); i++) {
        for (int j{i + 1}; j < possibleShips.size(); j++) {
            if (isIntersecting(possibleShips.at(i), possibleShips.at(j))) {
                invalidShipPositions.push_back(std::pair(possibleShips.at(i), possibleShips.at(j)));
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
        possibleBoards += int(candidateBoard.empty());
    }

    int i{}, j{};
    guess = {i, j};
    for (; i < 10; i++) {
        for (; j < 10; j++) {
            if (heatMap[i][j] > heatMap[guess.first][guess.second]) {
                guess = {i, j};
            }
        }
    }

    return guess;
}

std::pair<int, int> AiPlayer::Guess() {
    if (isHunting) {
        HuntingGuess();
    }
    else {
        ProbabilityGuess();
    }
}
