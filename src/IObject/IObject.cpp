#include "IObject.hpp"

long IObject::m_counter = 0;

IObject::IObject() {
    m_counter++;
    m_ID = m_counter;
}

IObject::~IObject() {
    m_counter--;
}

long IObject::getCounter() {
    return m_counter;
}

long IObject::getID() const {
    return m_ID;
}
