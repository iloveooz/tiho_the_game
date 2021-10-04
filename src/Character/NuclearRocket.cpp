#include "NuclearRocket.hpp"

NuclearRocket::NuclearRocket() {
    m_dDx = 0.0;
    m_dDy = 0.0;

    m_dSpeed = 10;
    m_dRadius = 32;

    m_iHealth = 10;
    m_iMaxHealth = 10;

    m_eRadiusType = Entity::eRadiusType::anyplace;
    m_sName = "nuclearrocket";
}

void NuclearRocket::update() {
    Entity::update();
}

void NuclearRocket::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}