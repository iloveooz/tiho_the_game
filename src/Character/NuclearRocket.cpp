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

    m_isStarted = false;

    m_iDamage = 500;
}

void NuclearRocket::update() {
    Entity::update();
    if (m_eMovingType == eMovingType::NO_MOVE && m_isStarted) {
        setDead();
    }
}

void NuclearRocket::doGo(sf::Vector2f& position) {
    if (!m_isStarted) {
        m_isStarted = true;
        Entity::doGo(position);
    }
}