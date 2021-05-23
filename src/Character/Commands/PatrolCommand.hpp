#ifndef TIHO_PATROLCOMMAND_HPP
#define TIHO_PATROLCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class PatrolCommand : UnitCommand {
    public:
        virtual ~PatrolCommand();

        void execute() override;
    };

}

#endif //TIHO_PATROLCOMMAND_HPP
