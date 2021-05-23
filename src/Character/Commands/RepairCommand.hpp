#ifndef TIHO_REPAIRCOMMAND_HPP
#define TIHO_REPAIRCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class RepairCommand : public UnitCommand {
    public:
        virtual ~RepairCommand();

        void execute() override;
    };

}

#endif //TIHO_REPAIRCOMMAND_HPP
