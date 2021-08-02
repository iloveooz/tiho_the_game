#ifndef TIHO_REPAIRCOMMAND_HPP
#define TIHO_REPAIRCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class RepairCommand : public UnitCommand {
    public:
        virtual ~RepairCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };

}

#endif //TIHO_REPAIRCOMMAND_HPP
