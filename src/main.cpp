#include <ctime>
#include <cmath>
#include "Game/Game.hpp"

int main() {

    srand(time(nullptr));

    Game game;
    game.run();

    return 0;
}
