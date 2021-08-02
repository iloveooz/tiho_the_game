#ifndef TIHO_DESTROYCOMMAND_HPP
#define TIHO_DESTROYCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class DestroyCommand : public UnitCommand {
    public:
        virtual ~DestroyCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };

}

#endif //TIHO_DESTROYCOMMAND_HPP
