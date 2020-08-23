#include <ctime>
#include <cmath>
#include "Game/Game.hpp"

int main() {

    srand(time(0));

    Game game;
    game.run();

    return 0;
}
