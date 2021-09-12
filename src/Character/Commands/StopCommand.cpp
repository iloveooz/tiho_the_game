#include "StopCommand.hpp"

namespace Commands {
    StopCommand::~StopCommand() {

    }

    void StopCommand::execute(std::unique_ptr<Entity>& character, sf::Vector2f position) {
        character->doStop(position);
    }
}