#ifndef TIHO_TANK_HPP
#define TIHO_TANK_HPP

#include "Entity.hpp"

class Tank : public Entity {
public:
    // конструктор
    Tank () {
        dx = rand() % 2 + 1;
        dy = rand() % 2 + 1;
        name = "tank";
    }

    void update();
};


#endif //TIHO_TANK_HPP
