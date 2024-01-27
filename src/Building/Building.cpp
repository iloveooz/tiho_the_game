#include "Building.hpp"
#include "ArsenalBuilding.hpp"
#include "CannonBuilding.hpp"
#include "FactoryBuilding.hpp"
#include "GeneratorBuilding.hpp"
#include "LaboratoryBuilding.hpp"
#include "MainBaseBuilding.hpp"
#include "MineBuilding.hpp"
#include "NuclearSiloBuilding.hpp"
#include "OilDerrickBuilding.hpp"

namespace Buildings {
    Building::Building() : m_bAlive(true), m_position(0.0, 0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0), m_cursor(sf::Sprite()) {
        m_healthBar.setSize(sf::Vector2f(62.f, 4.f));
        m_healthBar.setFillColor(sf::Color(255, 0, 0, 192));
        m_eRelationType = eRelationType::MINE;
    }

    std::unique_ptr<Building> Building::createBuilding(BuildID id) {
        switch (id) {
            case BuildID::arsenal:
                return std::unique_ptr<Building>(new ArsenalBuilding);
            case BuildID::cannon:
                return std::unique_ptr<Building>(new CannonBuilding);
            case BuildID::factory:
                return std::unique_ptr<Building>(new FactoryBuilding);
            case BuildID::gen:
                return std::unique_ptr<Building>(new GeneratorBuilding);
            case BuildID::lab:
                return std::unique_ptr<Building>(new LaboratoryBuilding);
            case BuildID::main:
                return std::unique_ptr<Building>(new MainBaseBuilding);
            case BuildID::mine:
                return std::unique_ptr<Building>(new MineBuilding);
            case BuildID::nsilo:
                return std::unique_ptr<Building>(new NuclearSiloBuilding);
            case BuildID::oil:
                return std::unique_ptr<Building>(new OilDerrickBuilding);
            default:
                assert(false);
        }
    }

    void Building::settings(Animations::BuildingAnimation &animation, double x, double y, double angle) {
        m_position.x = x;
        m_position.y = y;
        m_dAngle = angle;
        m_aAnimation = animation;
    }

    void Building::setColor() {
        if (m_eRelationType == eRelationType::ENEMY)
            m_aAnimation.getSprite().setColor(sf::Color(255,0,0, 192));
        else if (m_eRelationType == eRelationType::ALLY)
            m_aAnimation.getSprite().setColor(sf::Color(0,0,255, 192));
        else if (m_eRelationType == eRelationType::MINE)
            m_aAnimation.getSprite().setColor(sf::Color(0,128,128));
    }

    void Building::update() {
        if (m_sName != "explosion")
            m_healthBar.setSize(sf::Vector2f((m_iHealth * 62 / m_iMaxHealth), 4.f));
    }

    void Building::draw(sf::RenderWindow &app) {
        m_aAnimation.getSprite().setPosition((float) m_position.x, (float) m_position.y);
        m_aAnimation.getSprite().setRotation(m_dAngle);
        setColor();
        app.draw(m_aAnimation.getSprite());

        m_healthBar.setPosition(m_position.x - 32, m_position.y + 36);
        app.draw(m_healthBar);
    }

    std::string& Building::getName() {
        return m_sName;
    }

    bool Building::isAlive() const {
        return m_bAlive;
    }

    void Building::setDead() {
        m_iHealth = 0;
        m_bAlive = false;
    }

    void Building::setHealth(int value) {
        m_iHealth -= value;
        if (m_iHealth <= 0)
            setDead();
    }

    void Building::setSelected(bool value) {
        m_bSelected = value;
    }

    bool Building::isSelected() const {
        return m_bSelected;
    }

    sf::Sprite& Building::getSprite() {
        return m_aAnimation.getSprite();
    }

    sf::Vector2f& Building::getPosition() {
        return m_position;
    }

    ControlGame::Cursor& Building::getCursor() {
        return m_cursor;
    }

    void Building::setRelation(eRelationType type) {
        m_eRelationType = type;
    }

    eRelationType Building::getRelation() const {
        return m_eRelationType;
    }
}