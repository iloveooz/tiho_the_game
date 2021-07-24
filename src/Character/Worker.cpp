#include "Worker.hpp"

Worker::Worker() {
    m_dDx = 0.0;
    m_dDy = 0.0;
    m_sName = "worker";
}

void Worker::update(double dx, double dy) {
    m_position.x += m_dDx + dx;
    m_position.y += m_dDy + dy;

    if (m_position.x > Weight)
        m_position.x = 0;

    if (m_position.x < 0)
        m_position.x = Weight;

    if (m_position.y > Height)
        m_position.y = 0;

    if (m_position.y < 0)
        m_position.y = Height;
}