#include "IObject.hpp"

long IObject::m_lCounter = 0;

IObject::IObject() {
    m_lCounter++;
    m_lID = m_lCounter;
}

IObject::~IObject() {
    m_lCounter--;
}

long IObject::getCounter() {
    return m_lCounter;
}

long IObject::getID() const {
    return m_lID;
}
