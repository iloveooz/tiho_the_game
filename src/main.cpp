#include <ctime>
#include <cmath>
#include <iostream>

#include "Game/Game.hpp"

int main() {

    srand(time(nullptr));

    std::cout << "Start game" << std::endl;

    auto game = std::make_shared<Game>();
    game->run();

    return 0;
}
