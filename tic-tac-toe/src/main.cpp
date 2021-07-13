#include <iostream>
#include "Game/Game.hpp"
#include "Train/Train.hpp"
#include "Play/Play.hpp"
using namespace std;
int main()
{
    srand (time (0));
    /*auto train = Train("GaryOp", "DalenOp", 100000);
    train.start();*/

    auto play = Play("Human","DalenOp");
    play.start();
}