#include "GoCommand.hpp"

namespace Commands {
    GoCommand::~GoCommand() {

    }

    void GoCommand::execute(std::unique_ptr<Entity>& character, sf::Vector2f position) {
        character->doGo(position);
    }
}