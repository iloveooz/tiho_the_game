#ifndef TIHO_CAR_HPP
#define TIHO_CAR_HPP

#include <cmath>
#include "Entity.hpp"

class Car : public Entity {
public:
    // конструктор
    Car () {
        dx = sin(rand() % 2 + 1) * 2;
        dy = cos(rand() % 2 + 1) * 2;
        name = "car";
    }

    void update();
};


#endif //TIHO_CAR_HPP
