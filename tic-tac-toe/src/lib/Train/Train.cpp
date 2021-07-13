#include <random>
#include "Train/Train.hpp"
#include "Game/Game.hpp"
#include "Agent/Agent.hpp"

void Train::start()
{
    player1.set_name(player_name1);
    player2.set_name(player_name2);
    for (int i = 0; i < episode; i++)
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> chess(0, 1);
        int p1_chess = chess(rng);
        int p2_chess;
        if (p1_chess == 0)
            p2_chess = 1;
        else
            p2_chess = 0;
        player1.set_chess(p1_chess);
        player2.set_chess(p2_chess);
        Game new_game;
        while (1)
        {
            bool play = true;
            if (p1_chess < p2_chess)
            {
                if (play)
                    play &= player1.take_action(new_game);
                if (play)
                    play &= player2.take_action(new_game);
            }
            else
            {
                if (play)
                    play &= player2.take_action(new_game);
                if (play)
                    play &= player1.take_action(new_game);
            }
            if (!play)
                break;
        }
        player1.clear_last_state();
        player2.clear_last_state();
    }
    player1.write_memory();
    player2.write_memory();
}
