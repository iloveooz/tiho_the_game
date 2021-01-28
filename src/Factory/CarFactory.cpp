#include "CarFactory.hpp"
#include "../Character/Car.hpp"

std::unique_ptr<Entity> CarFactory::createEntity() {
    return std::unique_ptr<Entity>(new Car);
}
