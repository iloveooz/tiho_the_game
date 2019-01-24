//
// Created by fahr on 24.01.19.
//

#include "Tank.h"
#include <cmath>

const int Weight = 1600; // ширина главного окна
const int Height = 800;  // высота главного окна

void Tank::update() {
    // x += dx;
    // y += dy;

    x += sin(angle) * dx;
    y -= cos(angle) * dy;

    if (x > Weight) x = 0;
    if (x < 0) x = Weight;

    if (y > Height) y = 0;
    if (y < 0) y = Height;
}
