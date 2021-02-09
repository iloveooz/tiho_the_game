#ifndef TIHO_NUCLEARROCKET_HPP
#define TIHO_NUCLEARROCKET_HPP

#include "Entity.hpp"

class NuclearRocket : public Entity {
public:
    NuclearRocket();

    void update(double dx, double dy) override;
};

#endif //TIHO_NUCLEARROCKET_HPP
