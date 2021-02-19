#ifndef TIHO_HOLDPOSITIONCOMMAND_HPP
#define TIHO_HOLDPOSITIONCOMMAND_HPP

#include "UnitCommand.hpp"

class HoldPositionCommand : public UnitCommand {
public:
    virtual ~HoldPositionCommand();
    void execute() override {} ;
};

#endif //TIHO_HOLDPOSITIONCOMMAND_HPP
