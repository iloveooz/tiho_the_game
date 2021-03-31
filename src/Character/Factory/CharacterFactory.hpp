#ifndef TIHO_CHARACTERFACTORY_HPP
#define TIHO_CHARACTERFACTORY_HPP

#include "../Entity.hpp"

namespace Factory {
    enum CharID {
        car = 0,
        nuke,
        spit,
        tank,
        work
    };

    class CharacterFactory {
    public:
        CharacterFactory() {}

        virtual ~CharacterFactory() {}

        std::unique_ptr<Entity> createEntity(CharID charType) ;
    };
}

#endif //TIHO_CHARACTERFACTORY_HPP
