#include "Car.hpp"

Car::Car() {
    m_dDx = 1.0;
    m_dDy = 1.0;

    m_dSpeed = 3;
    m_dRadius = 4;

    m_iHealth = 100;
    m_iMaxHealth = 100;

    m_eRadiusType = Entity::eRadiusType::small;
    m_sName = "car";
}

void Car::update() {
    Entity::update();
}

void Car::doGo(sf::Vector2f& position) {
    Entity::doGo(position);
}
