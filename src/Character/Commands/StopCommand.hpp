#ifndef TIHO_STOPCOMMAND_HPP
#define TIHO_STOPCOMMAND_HPP

#include "UnitCommand.hpp"

namespace Commands {

    class StopCommand : public UnitCommand {
    public:
        virtual ~StopCommand();

        void execute(std::unique_ptr<Entity>& character, sf::Vector2f position) override;
    };
}

#endif //TIHO_STOPCOMMAND_HPP
