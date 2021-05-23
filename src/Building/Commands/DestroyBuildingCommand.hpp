#ifndef TIHO_DESTROYBUILDINGCOMMAND_HPP
#define TIHO_DESTROYBUILDINGCOMMAND_HPP

#include "BuildingCommand.hpp"

namespace Commands {
    class DestroyBuildingCommand : public BuildingCommand {
    public:
        virtual ~DestroyBuildingCommand();

        void execute() override;
    };
}

#endif //TIHO_DESTROYBUILDINGCOMMAND_HPP
