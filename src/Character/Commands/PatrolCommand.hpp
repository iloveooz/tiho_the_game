#ifndef TIHO_PATROLCOMMAND_HPP
#define TIHO_PATROLCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class PatrolCommand : public UnitCommand {
    public:
        virtual ~PatrolCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };

}

#endif //TIHO_PATROLCOMMAND_HPP
