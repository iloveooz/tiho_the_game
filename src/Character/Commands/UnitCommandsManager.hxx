#ifndef TIHO_UNITCOMMANDSMANAGER_HXX
#define TIHO_UNITCOMMANDSMANAGER_HXX

#include "UnitCommand.hpp"

namespace Commands {
    class UnitCommandsManager {
    public:
        UnitCommandsManager();
        void handleCommand(UnitAction type, std::unique_ptr<Entity>& entity, sf::Vector2f position);

    private:
        std::map<UnitAction, std::unique_ptr<Commands::UnitCommand>> m_mCommands;
    };
}

#endif //TIHO_UNITCOMMANDSMANAGER_HXX
