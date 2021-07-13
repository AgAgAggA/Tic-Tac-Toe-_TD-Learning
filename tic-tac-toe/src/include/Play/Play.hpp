#pragma once
#include <string>
#include "Game/Game.hpp"
#include "Agent/Agent.hpp"

class Play
{
    std::string player_n, robot_n;
    Agent robot;

public:
    Play(std::string player_name, std::string robot_name) : player_n(player_name), robot_n(robot_name) {}
    void start();
};