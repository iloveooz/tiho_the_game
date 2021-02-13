#include <ctime>
#include <cmath>
#include "Game/Game.hpp"

int main() {

    srand(time(nullptr));

    auto game = std::make_shared<Game>();
    game->run();

    return 0;
}
