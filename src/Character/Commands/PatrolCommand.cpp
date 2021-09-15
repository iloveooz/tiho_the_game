#include "PatrolCommand.hpp"

namespace Commands {
    PatrolCommand::~PatrolCommand() {

    }

    void PatrolCommand::execute(std::unique_ptr<Entity>& character, sf::Vector2f position) {
        character->doPatrol(position);
    }
}