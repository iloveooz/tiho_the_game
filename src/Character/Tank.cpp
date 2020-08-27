#include "Tank.hpp"

Tank::Tank() {
    m_dDx = rand() % 2 + 1;
    m_dDy = rand() % 2 + 1;
    m_sName = "tank";
}

void Tank::update() {
    m_dX += sin(m_dAngle) * m_dDx;
    m_dY -= cos(m_dAngle) * m_dDy;

    if (m_dX > Weight) m_dX = 0;
    if (m_dX < 0) m_dX = Weight;

    if (m_dY > Height) m_dY = 0;
    if (m_dY < 0) m_dY = Height;
}