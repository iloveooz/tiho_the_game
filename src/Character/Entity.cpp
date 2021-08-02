#include "Entity.hpp"

Entity::Entity() : m_bAlive(true), m_position(0.0, 0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0) {}

void Entity::settings(Animations::Animation &animation, double x, double y, double angle) {
    m_position.x = x;
    m_position.y = y;
    m_dAngle = angle;
    m_aAnimation = animation;
    m_bIsMoving = false;
}

void Entity::doGo(sf::Vector2f& position) {
    m_targetPosition = position;
    m_bIsMoving = true;

    double a = m_position.x - m_targetPosition.x;
    double b = m_position.y - m_targetPosition.y;

    m_dAngle = angleAdjust + ((atan2(b, a)) * 180) / PI;

    m_aAnimation.getSprite().setRotation(m_dAngle);
}

void Entity::update() {
    if (m_bIsMoving) {

        m_dDx = cos((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;
        m_dDy = sin((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;

        m_position.x += m_dDx;
        m_position.y += m_dDy;
    }

    double distance = sqrt(pow((m_targetPosition.x - m_position.x), 2) + pow((m_targetPosition.y - m_position.y), 2));

    if (distance < m_dRadius)
        m_bIsMoving = false;
}

void Entity::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_position.x, (float) m_position.y);
    m_aAnimation.getSprite().setRotation(m_dAngle);
    m_aAnimation.getSprite().setColor(sf::Color(0,128,128));
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

bool Entity:: isMoving() const {
    return m_bIsMoving;
}

