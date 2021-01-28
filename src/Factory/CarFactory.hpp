#ifndef TIHO_CARFACTORY_HPP
#define TIHO_CARFACTORY_HPP

#include "CharacterFactory.hpp"

class CarFactory : public CharacterFactory {
public:
    CarFactory() {}
    virtual ~CarFactory() {}

    std::unique_ptr<Entity> createEntity() override;
};

#endif //TIHO_CARFACTORY_HPP
