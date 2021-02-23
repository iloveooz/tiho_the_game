#include "Entity.hpp"

Entity::Entity() : m_bAlive(true), m_dX(0.0), m_dY(0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0) {}

void Entity::settings(Animations::CharacterAnimation &animation, double x, double y, double angle) {
    m_dX = x;
    m_dY = y;
    m_dAngle = angle;
    m_aAnimation = animation;
}

void Entity::update(double dx, double dy) {}

void Entity::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_dX, (float) m_dY);
    m_aAnimation.getSprite().setRotation(m_dAngle);
    m_aAnimation.getSprite().setColor(sf::Color::Red);
    app.draw(m_aAnimation.getSprite());
}

std::string& Entity::getName() {
    return m_sName;
}

bool Entity::isAlive() const {
    return m_bAlive;
}
