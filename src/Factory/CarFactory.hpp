#ifndef TIHO_CARFACTORY_HPP
#define TIHO_CARFACTORY_HPP

#include "CharacterFactory.hpp"

class CarFactory : public CharacterFactory {
public:
    CarFactory() {}
    virtual ~CarFactory() {}

    Entity* createEntity() override;
};

#endif //TIHO_CARFACTORY_HPP
