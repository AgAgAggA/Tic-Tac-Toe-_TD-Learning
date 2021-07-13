#pragma once
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>

class Game
{
    std::vector<int> board;
    std::vector<int> valid_action;

public:
    Game() { board.resize(9,0); }
    const std::vector<int> &get_board() const { return board; }
    std::string get_board_str()
    {
        std::stringstream state;
        std::copy(board.begin(), board.end(), std::ostream_iterator<int>(state));
        return state.str();
    }
    void write_board(int chess_id, int position) { board[position] = chess_id; }
    void clear_board(int position) { board[position] = 0; }
    bool action_valid(int position)
    {
        bool valid = position == 0 ? true : false;
        return valid;
    }
    bool check_if_end();
    void print_board();
    void set_valid_action();
    const std::vector<int> &get_valid_action() const { return valid_action; }
};