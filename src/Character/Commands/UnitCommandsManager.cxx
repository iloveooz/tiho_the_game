#include "UnitCommandsManager.hxx"

#include "DestroyCommand.hpp"
#include "RepairCommand.hpp"
#include "AttackCommand.hpp"
#include "PatrolCommand.hpp"
#include "HoldPositionCommand.hpp"
#include "StopCommand.hpp"
#include "GoCommand.hpp"

namespace Commands {
    UnitCommandsManager::UnitCommandsManager() {
        m_mCommands.insert(std::make_pair(UnitAction::Go, new Commands::GoCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Stop, new Commands::StopCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Hold, new Commands::HoldPositionCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Patrol, new Commands::PatrolCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Attack, new Commands::AttackCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Repair, new Commands::RepairCommand()));
        m_mCommands.insert(std::make_pair(UnitAction::Destroy, new Commands::DestroyCommand()));
    }

    void UnitCommandsManager::handleCommand(UnitAction type, std::unique_ptr<Entity>& entity, sf::Vector2f position) {
        auto command = m_mCommands.find(type);
        assert(command != m_mCommands.end());

        command->second->execute(entity, position);
    }
}
