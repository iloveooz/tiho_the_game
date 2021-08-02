#ifndef TIHO_GOCOMMAND_HPP
#define TIHO_GOCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class GoCommand : public UnitCommand {
    public:
        virtual ~GoCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };

}

#endif //TIHO_GOCOMMAND_HPP
