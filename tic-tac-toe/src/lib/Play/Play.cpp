#include <random>
#include <iostream>
#include "Play/Play.hpp"
#include "Game/Game.hpp"
#include "Agent/Agent.hpp"

using namespace std;
void Play::start()
{
    robot.set_name(robot_n);
    robot.read_memory();
    cout << player_n << " v.s. " << robot_n << "\n";
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> chess(0, 1);
    int p1_chess = chess(rng);
    int p2_chess;
    if (p1_chess == 0)
        p2_chess = 1;
    else
        p2_chess = 0;
    robot.set_chess(p1_chess);
    std::unordered_map<int, char> chess_table = {{0, 'o'}, {1, 'x'}};
    cout << robot_n << " play " << chess_table[p1_chess] << "\n";
    cout << player_n << " play " << chess_table[p2_chess] << "\n";

    for (int i = 0; i < 9; i++)
    {
        cout << i;
        if (i % 3 == 2 && i != 8)
            cout << "\n----------\n";
        else if (i != 8)
            cout << " | ";
    }
    cout << "\n";

    Game new_game;
    while (1)
    {
        int player_action;
        if (p1_chess < p2_chess)
        {
            cout <<robot_n <<" play ! \n";
            robot.take_action_play(new_game);
            new_game.print_board();
            new_game.set_valid_action();
            if (new_game.check_if_end() || new_game.get_valid_action().size() == 0)
                break;
            cout << "-------------------------- \n";
            cout << "please input action \n";
            cin >> player_action;
            new_game.write_board(p2_chess + 1, player_action);
            new_game.print_board();
            if (new_game.check_if_end() || new_game.get_valid_action().size() == 0)
                break;
        }
        else
        {
            new_game.set_valid_action();
            if (new_game.get_valid_action().size() == 0 || new_game.check_if_end())
                break;
            cout << "-------------------------- \n";
            cout << "please input action \n";
            cin >> player_action;
            new_game.write_board(p2_chess + 1, player_action);
            new_game.print_board();
            if (new_game.check_if_end() || new_game.get_valid_action().size() == 0)
                break;
            cout << "-------------------------- \n";
            cout <<robot_n <<" play ! \n";
            robot.take_action_play(new_game);
            new_game.print_board();
        }
    }
}