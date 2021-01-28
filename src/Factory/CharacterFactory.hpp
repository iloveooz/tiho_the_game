#ifndef TIHO_CHARACTERFACTORY_HPP
#define TIHO_CHARACTERFACTORY_HPP

#include "../Character/Entity.hpp"

class CharacterFactory {
public:
    CharacterFactory() {}
    virtual ~CharacterFactory() {}

    virtual std::unique_ptr<Entity> createEntity() = 0;
};

#endif //TIHO_CHARACTERFACTORY_HPP
