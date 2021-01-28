#ifndef TIHO_TANKFACTORY_HPP
#define TIHO_TANKFACTORY_HPP

#include "CharacterFactory.hpp"

class TankFactory : public CharacterFactory {
public:
    TankFactory() {}
    virtual ~TankFactory() {}

    std::unique_ptr<Entity> createEntity() override;
};

#endif //TIHO_TANKFACTORY_HPP
