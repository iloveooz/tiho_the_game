#ifndef TIHO_BUILDINGCOMMAND_HPP
#define TIHO_BUILDINGCOMMAND_HPP

#include "../Building.hpp"

using Buildings::Building;

namespace Commands {
    enum class BuildingAction {
        Nothing,
        Destroy,
        Count
    };

    class BuildingCommand {
    public:
        virtual ~BuildingCommand();

        virtual void execute() = 0;

    private:
        Building m_building;
    };
}
#endif //TIHO_BUILDINGCOMMAND_HPP