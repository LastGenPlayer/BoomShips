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


class AiPlayer : public Game {
public:
    Game currenGame;
    std::vector<std::pair<int, int>> targets;
    bool isHunting;

    explicit AiPlayer(Game game) : currenGame(game), targets({}), isHunting(false) {};

    std::pair<int, int> RandomGuess();
    std::pair<int, int> HuntingGuess();
    std::pair<int, int> ProbabilityGuess();
    std::pair<int, int> Guess();
};



#endif //AIPLAYER_H
