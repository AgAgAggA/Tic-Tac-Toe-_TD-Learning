#include <vector>
#include <unordered_map>
#include <iostream>
#include "Game/Game.hpp"
using namespace std;
void Game::print_board()
{
    std::unordered_map<int, char> chess_table = {{0, ' '}, {1, 'o'}, {2, 'x'}};
    for (int i = 0; i < 9; i++)
    {
        cout << chess_table[board[i]];
        if (i % 3 == 2 && i != 8)
            cout << "\n----------\n";
        else if (i != 8)
            cout << " | ";
    }
    cout << "\n";
}
bool is_equal(int a, int b, int c)
{
    return ((a == b) && (a == c) && (a != 0));
}
bool Game::check_if_end()
{
    for (int i = 0; i < 3; i++)
    {
        if (is_equal(board[i * 3], board[i * 3 + 1], board[i * 3 + 2]))
        {
            return true;
        }
        if (is_equal(board[0 * 3 + i], board[1 * 3 + i], board[2 * 3 + i]))
        {
            return true;
        }
    }
    if (is_equal(board[0], board[4], board[8]))
        return true;
    if (is_equal(board[2], board[4], board[6]))
        return true;
    return false;
}
void Game::set_valid_action()
{
    valid_action.clear();
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == 0)
        {
            valid_action.emplace_back(i);
        }
    }
}