#ifndef TIHO_DESTROYCOMMAND_HPP
#define TIHO_DESTROYCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class DestroyCommand : public UnitCommand {
    public:
        virtual ~DestroyCommand();

        void execute() override;
    };

}

#endif //TIHO_DESTROYCOMMAND_HPP
