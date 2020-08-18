#include "IObject.hpp"

long IObject::counter = 0;

IObject::IObject() {
    counter++;
    ID = counter;
}

IObject::~IObject() {
    counter--;
}

long IObject::getCounter() {
    return counter;
}

long IObject::getID() const {
    return ID;
}
