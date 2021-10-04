#include "Worker.hpp"

Worker::Worker() {
    m_dDx = 0.0;
    m_dDy = 0.0;

    m_dSpeed = 2;
    m_dRadius = 16;

    m_iHealth = 60;
    m_iMaxHealth = 60;

    m_eRadiusType = Entity::eRadiusType::close;
    m_sName = "worker";
}

void Worker::update() {
    Entity::update();
}

void Worker::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}