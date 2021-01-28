#include "TankFactory.hpp"
#include "../Character/Tank.hpp"

std::unique_ptr<Entity> TankFactory::createEntity() {
    return std::unique_ptr<Entity>(new Tank);
}
