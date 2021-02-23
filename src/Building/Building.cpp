#include "Building.hpp"

Building::Building() : m_bAlive(true), m_dX(0.0), m_dY(0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0) {}

void Building::settings(Animations::BuildingAnimation &animation, double x, double y, double angle) {
    m_dX = x;
    m_dY = y;
    m_dAngle = angle;
    m_aAnimation = animation;
}

void Building::update(double dx, double dy) {}

void Building::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_dX, (float) m_dY);
    m_aAnimation.getSprite().setRotation(m_dAngle);
    m_aAnimation.getSprite().setColor(sf::Color::Red);
    app.draw(m_aAnimation.getSprite());
}

std::string& Building::getName() {
    return m_sName;
}

bool Building::isAlive() const {
    return m_bAlive;
}