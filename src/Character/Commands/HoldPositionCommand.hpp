#ifndef TIHO_HOLDPOSITIONCOMMAND_HPP
#define TIHO_HOLDPOSITIONCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class HoldPositionCommand : public UnitCommand {
    public:
        virtual ~HoldPositionCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };

}

#endif //TIHO_HOLDPOSITIONCOMMAND_HPP
