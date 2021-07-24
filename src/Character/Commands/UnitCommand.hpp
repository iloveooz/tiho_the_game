#ifndef TIHO_UNITCOMMAND_HPP
#define TIHO_UNITCOMMAND_HPP

namespace Commands {
    enum class UnitAction {
        Nothing,
        Go,
        Stop,
        Hold,
        Patrol,
        Attack,
        Repair,
        Destroy,
        Count
    };

    class UnitCommand {
    public:
        virtual ~UnitCommand();

        virtual void execute() = 0;
    };
}

#endif //TIHO_UNITCOMMAND_HPP
