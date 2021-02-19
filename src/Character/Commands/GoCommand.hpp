#ifndef TIHO_GOCOMMAND_HPP
#define TIHO_GOCOMMAND_HPP

#include "UnitCommand.hpp"

class GoCommand : public UnitCommand {
public:
    virtual ~GoCommand();
    void execute() override {} ;
};

#endif //TIHO_GOCOMMAND_HPP
