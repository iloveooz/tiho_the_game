#include "TankFactory.hpp"
#include "../Character/Tank.hpp"

Entity *TankFactory::createEntity() {
    return new Tank;
}
