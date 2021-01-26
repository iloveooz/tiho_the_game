#include "Worker.hpp"

Worker::Worker() {
    m_dDx = 0.0;
    m_dDy = 0.0;
    m_sName = "worker";
}

void Worker::update(double dx, double dy) {
    m_dX += m_dDx + dx;
    m_dY += m_dDy + dy;

    if (m_dX > Weight) m_dX = 0;
    if (m_dX < 0) m_dX = Weight;

    if (m_dY > Height) m_dY = 0;
    if (m_dY < 0) m_dY = Height;
}