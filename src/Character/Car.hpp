#ifndef TIHO_CAR_HPP
#define TIHO_CAR_HPP

#include "Entity.hpp"

class Car : public Entity {
public:
    Car();

    void update() override;
};

#endif //TIHO_CAR_HPP
