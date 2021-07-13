#pragma once
#include <unordered_map>
#include <utility>
#include <vector>
#include <string>
#include "Game/Game.hpp"

class Agent
{
    bool first;
    int chess_color; // must minus one
    std::string myname;
    std::string last_state = "";
    std::string fail_state;
    std::unordered_map<std::string, std::vector<double>> state_action_dict;

public:
    bool take_action(Game &);
    void take_action_play(Game &);
    void read_memory();
    void write_memory();
    void set_chess(int i) { chess_color = i; }
    void set_name(std::string name) { myname = name; }
    void clear_last_state(){last_state = "";}
};
