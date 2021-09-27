#include "Entity.hpp"

Entity::Entity() : m_bAlive(true), m_position(0.0, 0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0), m_cursor(sf::Sprite()) {}

void Entity::settings(Animations::Animation &animation, double x, double y, double angle) {
    m_position.x = x;
    m_position.y = y;
    m_dAngle = angle;
    m_aAnimation = animation;
    m_eMovingType = eMovingType::NO_MOVE;

    if (m_sName != "explosion") {
        m_healthBar.setSize(sf::Vector2f(100.f, 4.f));
        m_healthBar.setFillColor(sf::Color(255, 0, 0, 192));
    }
}

void Entity::setAngle() {
    double a = m_position.x - m_targetPosition.x;
    double b = m_position.y - m_targetPosition.y;

    m_dAngle = ((m_eMovingType == eMovingType::HOLDING) ? -angleAdjust : angleAdjust) + ((atan2(b, a)) * 180) / PI;

    m_aAnimation.getSprite().setRotation(m_dAngle);
}

void Entity::doGo(sf::Vector2f& position) {
    m_targetPosition = position;
    m_eMovingType = eMovingType::MOVING;
    setAngle();
}

void Entity::doPatrol(sf::Vector2f& position) {
    m_targetPosition = position;
    m_beginPosition = m_position;
    m_eMovingType = eMovingType::PATROLLING;
    setAngle();
}

void Entity::doHold(sf::Vector2f& position) {
    m_eMovingType = eMovingType::HOLDING;

    if (position.x != 0 && position.y != 0) {
        m_targetPosition = position;
        setAngle();
    }
}

void Entity::doStop(sf::Vector2f& position) {
    m_eMovingType = eMovingType::NO_MOVE;
}

void Entity::update() {
    if (m_eMovingType == eMovingType::MOVING) {
        m_dDx = cos((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;
        m_dDy = sin((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;

        m_position.x += m_dDx;
        m_position.y += m_dDy;

        double distance = sqrt(pow((m_targetPosition.x - m_position.x), 2) + pow((m_targetPosition.y - m_position.y), 2));

        if (distance < m_dRadius) {
            m_eMovingType = eMovingType::NO_MOVE;
        }
    }

    if (m_eMovingType == eMovingType::PATROLLING) {
        m_dDx = cos((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;
        m_dDy = sin((angleAdjust + m_dAngle) * PI / 180) * m_dSpeed;

        m_position.x += m_dDx;
        m_position.y += m_dDy;

        double distance = sqrt(pow((m_targetPosition.x - m_position.x), 2) + pow((m_targetPosition.y - m_position.y), 2));

        if (distance < m_dRadius) {
            std::swap(m_beginPosition, m_targetPosition);
            setAngle();
        }
    }

    if (m_eMovingType == eMovingType::HOLDING) {
        m_eMovingType = eMovingType::NO_MOVE;
    }

    if (m_sName != "explosion")
        m_healthBar.setSize(sf::Vector2f((m_iHealth * 100 / m_iMaxHealth), 4.f));
}

void Entity::draw(sf::RenderWindow &app) {
    m_aAnimation.getSprite().setPosition((float) m_position.x, (float) m_position.y);
    m_aAnimation.getSprite().setRotation(m_dAngle);
    m_aAnimation.getSprite().setColor(sf::Color(0,128,128));

    m_healthBar.setPosition(m_position.x - 50, m_position.y + 56);

    app.draw(m_aAnimation.getSprite());

    if (m_bAlive)
        app.draw(m_healthBar);
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

void Entity::setDead() {
    m_iHealth = 0;
    m_bAlive = false;
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

bool Entity::isMoving() const {
    if (m_eMovingType == eMovingType::NO_MOVE)
        return false;
    else
        return true;
}

ControlGame::Cursor& Entity::getCursor() {
    return m_cursor;
}

