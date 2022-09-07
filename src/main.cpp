#include <ctime>
#include <cmath>
#include <iostream>

#include "Game/Game.hpp"

int main() {

    srand(time(nullptr));

    auto game = std::make_shared<Game>();

    game->getConsoleLogger()->log(__PRETTY_FUNCTION__, "Start!");
    game->run();
    game->getConsoleLogger()->log(__PRETTY_FUNCTION__, "End!");

    return 0;
}
