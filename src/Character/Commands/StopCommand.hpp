#ifndef TIHO_STOPCOMMAND_HPP
#define TIHO_STOPCOMMAND_HPP

#include "UnitCommand.hpp"

class StopCommand : public UnitCommand {
public:
    virtual ~StopCommand();
    void execute() override {} ;
};

#endif //TIHO_STOPCOMMAND_HPP
