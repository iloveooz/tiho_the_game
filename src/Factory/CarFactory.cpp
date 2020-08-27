#include "CarFactory.hpp"
#include "../Character/Car.hpp"

Entity *CarFactory::createEntity() {
    return new Car;
}
