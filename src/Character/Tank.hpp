#ifndef TIHO_TANK_HPP
#define TIHO_TANK_HPP

#include "Entity.hpp"

class Tank : public Entity {
public:
    Tank();

    void update(double dx, double dy) override;
};

#endif //TIHO_TANK_HPP
