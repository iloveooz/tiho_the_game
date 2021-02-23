#ifndef TIHO_ATTACKCOMMAND_HPP
#define TIHO_ATTACKCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class AttackCommand : public UnitCommand {
    public:
        virtual ~AttackCommand();

        void execute() override {};
    };

}

#endif //TIHO_ATTACKCOMMAND_HPP
