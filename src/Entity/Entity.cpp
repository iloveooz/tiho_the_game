#include "Entity.hpp"

// TODO - сделать инициализацию
Entity::Entity() {
    m_bAlive = true;
    m_dX = 0;
    m_dY = 0;
    m_dDx = 0;
    m_dDy = 0;
    m_dAngle = 0;
}

void Entity::settings(Animation &animation, double x, double y, double angle) {
    m_dX = x;
    m_dY = y;
    m_dAngle = angle;
    m_aAnimation = animation;
}

void Entity::update() {}

void Entity::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_dX, (float) m_dY);
    m_aAnimation.getSprite().setRotation(m_dAngle + m_dX);
    m_aAnimation.getSprite().setColor(sf::Color::Green);
    app.draw(m_aAnimation.getSprite());
}