#include "CarFactory.hpp"
#include "../Car.hpp"

std::unique_ptr<Entity> CarFactory::createEntity() {
    return std::unique_ptr<Entity>(new Car);
}
