#include "Car.hpp"

Car::Car() {
    m_dDx = rand() % 2 + 1;
    m_dDy = rand() % 2 + 1;
    m_sName = "car";
}

void Car::update() {
    m_dX += m_dDx;
    m_dY += m_dDy;

    if (m_dX > Weight) m_dX = 0;
    if (m_dX < 0) m_dX = Weight;

    if (m_dY > Height) m_dY = 0;
    if (m_dY < 0) m_dY = Height;
}