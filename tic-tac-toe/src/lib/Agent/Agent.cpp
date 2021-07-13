#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include "Agent/Agent.hpp"
#include "Game/Game.hpp"
#include <random>
#include <iomanip>

using namespace std;

void check_state(unordered_map<string, vector<double>> &state_action_dict, string state, int lose)
{
    if (lose < 2)
    {
        if (state_action_dict.find(state) == state_action_dict.end())
        {
            state_action_dict[state].resize(2, 0);
            state_action_dict[state][lose] = 0;
            state_action_dict[state][1 - lose] = 1;
        }
    }
    else
    {
        if (state_action_dict.find(state) == state_action_dict.end())
        {
            state_action_dict[state].resize(2, 0.5);
        }
    }
}
void set_state(Game &now_game, unordered_map<string, vector<double>> &state_action_dict, string last_state, int chess_color, int lose)
{
    string now_state = now_game.get_board_str();
    check_state(state_action_dict, now_state, lose);
    check_state(state_action_dict, last_state, 2);
    double v_st = state_action_dict[last_state][chess_color];
    double n_st = state_action_dict[now_state][chess_color];
    state_action_dict[last_state][chess_color] += (0.1 * (n_st - v_st));
}
void Agent::take_action_play(Game &now_game)
{
    now_game.set_valid_action();
    auto valid_action = now_game.get_valid_action();
    double best_value = 0;
    int best_action = 0;
    for (auto &action : valid_action)
    {
        now_game.write_board(chess_color + 1, action);
        string now_state = now_game.get_board_str();
        if (state_action_dict.find(now_state) == state_action_dict.end())
        {
            state_action_dict[now_state].resize(2, 0.5);
        }
        if (state_action_dict[now_state][chess_color] > best_value)
        {
            best_value = state_action_dict[now_state][chess_color];
            best_action = action;
        }
        now_game.clear_board(action);
    }
    now_game.write_board(chess_color + 1, best_action);
}

bool Agent::take_action(Game &now_game)
{
    if (now_game.check_if_end())
    {
        set_state(now_game, state_action_dict, last_state, chess_color, chess_color);
        return false;
    }
    now_game.set_valid_action();
    auto valid_action = now_game.get_valid_action();
    double best_value = 0;
    int best_action = 0;
    if (valid_action.size() == 0)
    {
        set_state(now_game, state_action_dict, last_state, chess_color, 2);
        return false;
    }
    random_shuffle(valid_action.begin(), valid_action.end());
    for (auto &action : valid_action)
    {
        now_game.write_board(chess_color + 1, action);
        string now_state = now_game.get_board_str();
        bool end_game = now_game.check_if_end();
        if (end_game)
        {
            set_state(now_game, state_action_dict, last_state, chess_color, 1 - chess_color);
        }
        else
        {
            set_state(now_game, state_action_dict, last_state, chess_color, 2);
        }
        if (state_action_dict[now_state][chess_color] > best_value)
        {
            best_value = state_action_dict[now_state][chess_color];
            best_action = action;
        }
        now_game.clear_board(action);
    }
    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<double> distr(0, 1);
    if (distr(eng) > 0.1)
    {
        now_game.write_board(chess_color + 1, best_action);
    }
    else
    {
        now_game.write_board(chess_color + 1, valid_action[0]);
    }
    auto now_board = now_game.get_board();
    last_state = now_game.get_board_str();
    return true;
}

void Agent::read_memory()
{

    ifstream memory(myname + ".txt",ios::in);
    if (memory.is_open())
    {
        string state;
        double v1,v2;
        while (memory>>state>>v1>>v2)
        {
            vector<double> value;
            value.emplace_back(v1);
            value.emplace_back(v2);
            state_action_dict[state] = value;
        }
        memory.close();
    }
}
void Agent::write_memory()
{
    ofstream memory;
    memory.open(myname + ".txt");
    for (auto &state : state_action_dict)
    {
        if(state.first == "")
            continue;
        memory << state.first;
        for (auto &value : state.second)
        {
            memory << " " << value;
        }
        memory << "\n";
    }
}