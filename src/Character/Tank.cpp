#include "Tank.hpp"

Tank::Tank() {
    m_dDx = 0.0;
    m_dDy = 0.0;

    m_dSpeed = 1;
    m_dRadius = 4;

    m_iHealth = 180;
    m_iMaxHealth = 180;

    m_eRadiusType = Entity::eRadiusType::far;
    m_sName = "tank";
}

void Tank::update() {
    Entity::update();
}

void Tank::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}