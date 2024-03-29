#include "SpitFire.hpp"

SpitFire::SpitFire() {
    m_dDx = 0.0;
    m_dDy = 0.0;

    m_dSpeed = 2;
    m_dRadius = 16;

    m_iHealth = 200;
    m_iMaxHealth = 200;

    m_eRadiusType = Entity::eRadiusType::middle;
    m_sName = "spitfire";
}

void SpitFire::update() {
    Entity::update();
}

void SpitFire::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}