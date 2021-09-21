#include "Worker.hpp"

Worker::Worker() {
    m_dDx = 0.0;
    m_dDy = 0.0;

    m_dSpeed = 2;
    m_dRadius = 4;

    m_iHealth = 60;
    m_sName = "worker";
}

void Worker::update() {
    Entity::update();
}

void Worker::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}