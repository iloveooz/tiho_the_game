#ifndef TIHO_NUCLEARROCKET_HPP
#define TIHO_NUCLEARROCKET_HPP

#include "Entity.hpp"

class NuclearRocket : public Entity {
public:
    NuclearRocket();

    void doGo(sf::Vector2f& position) override;

    void update() override;

private:
    bool m_isStarted;
};

#endif //TIHO_NUCLEARROCKET_HPP
