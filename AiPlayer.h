//
// Created by Rain Verrev on 24.05.2024.
//

#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "Game.h"
#include <vector>
#include <map>
#include <set>
#include <random>


class AiPlayer : public Board {
public:
    Board playerBoard;
    std::vector<std::pair<int, int>> targets;
    bool isHunting;
    bool stageOne;
    std::vector<Board> stageOneBoards;
    std::vector<int> blacklist;

    explicit AiPlayer(Board B) : playerBoard(B), targets({}), isHunting(false), stageOne(true) {
        stageOnePrep();
    };

    std::pair<int, int> RandomGuess();
    std::pair<int, int> StageOneGuess();
    std::pair<int, int> HuntingGuess();
    std::pair<int, int> ProbabilityGuess();
    std::pair<int, int> Guess();
    static void randomBoard(Board&);
    void stageOnePrep();
    bool checkVector(std::vector<int>, int);

};



#endif //AIPLAYER_H
