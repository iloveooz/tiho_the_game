#include "Entity.hpp"

Entity::Entity() : m_bAlive(true), m_position(0.0, 0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0) {}

void Entity::settings(Animations::Animation &animation, double x, double y, double angle) {
    m_position.x = x;
    m_position.y = y;
    m_dAngle = angle;
    m_aAnimation = animation;
}

void Entity::update(double dx, double dy) {}

void Entity::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_position.x, (float) m_position.y);
    m_aAnimation.getSprite().setRotation(m_dAngle);
    m_aAnimation.getSprite().setColor(sf::Color::Red);
    app.draw(m_aAnimation.getSprite());
}

void Entity::setName(const std::string& name) {
    m_sName = name;
}

std::string& Entity::getName() {
    return m_sName;
}

bool Entity::isAlive() const {
    return m_bAlive;
}

Animations::Animation &Entity::getAnimation() {
    return m_aAnimation;
}

sf::Vector2f &Entity::getPosition() {
    return m_position;
}

sf::Sprite &Entity::getSprite() {
    return m_aAnimation.getSprite();
}

void Entity::setSelected(bool value) {
    m_bSelected = value;
}

bool Entity::isSelected() const {
    return m_bSelected;
}