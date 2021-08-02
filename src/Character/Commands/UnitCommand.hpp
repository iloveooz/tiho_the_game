#ifndef TIHO_UNITCOMMAND_HPP
#define TIHO_UNITCOMMAND_HPP

#include "../Entity.hpp"

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

        virtual void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) = 0;

    protected:
        UnitAction m_actionType;
    };
}

#endif //TIHO_UNITCOMMAND_HPP
