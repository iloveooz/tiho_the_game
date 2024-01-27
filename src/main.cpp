#include <ctime>
#include <cmath>

#include "Game/Game.hpp"

/*
 * TIHO planet, 2019 - 2024
 *
 */

int main() {
    srand(time(nullptr));

    auto game = std::make_shared<Game>();
    game->run();

    return 0;
}
