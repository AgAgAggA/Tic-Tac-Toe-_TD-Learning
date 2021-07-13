#pragma once
#include <string>
#include "Game/Game.hpp"
#include "Agent/Agent.hpp"

class Train
{
    std::string player_name1, player_name2;
    int episode;
    Agent player1, player2;

public:
    Train(std::string name_1, std::string name_2, int iter) : player_name1(name_1), player_name2(name_2), episode(iter) {}
    void start();
};