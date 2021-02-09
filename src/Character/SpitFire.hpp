#ifndef TIHO_SPITFIRE_HPP
#define TIHO_SPITFIRE_HPP

#include "Entity.hpp"

class SpitFire : public Entity {
public:
    SpitFire();

    void update(double dx, double dy) override;
};

#endif //TIHO_SPITFIRE_HPP
