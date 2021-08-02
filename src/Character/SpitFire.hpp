#ifndef TIHO_SPITFIRE_HPP
#define TIHO_SPITFIRE_HPP

#include "Entity.hpp"

class SpitFire : public Entity {
public:
    SpitFire();

    void doGo(sf::Vector2f& position) override;

    void update() override;
};

#endif //TIHO_SPITFIRE_HPP
