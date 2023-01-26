#include <ctime>
#include <cmath>

#include "Game/Game.hpp"

/*
 * TIHO planet, 2019 - 2023
 *
 */

int main() {

    srand(time(nullptr));

    auto game = std::make_shared<Game>();

    game->getConsoleLogger()->log(__PRETTY_FUNCTION__, "Start!");
    game->run();
    game->getConsoleLogger()->log(__PRETTY_FUNCTION__, "End!");

    return 0;
}
