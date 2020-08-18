#ifndef TIHO_TANK_H
#define TIHO_TANK_H

#include "Entity.h"

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


#endif //TIHO_TANK_H
