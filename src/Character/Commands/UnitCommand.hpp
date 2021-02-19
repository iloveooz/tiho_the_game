#ifndef TIHO_UNITCOMMAND_HPP
#define TIHO_UNITCOMMAND_HPP

class UnitCommand {
public:
    virtual ~UnitCommand();
    virtual void execute() = 0;
};

#endif //TIHO_UNITCOMMAND_HPP
