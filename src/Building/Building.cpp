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
    Building::Building() : m_bAlive(true), m_dX(0.0), m_dY(0.0), m_dDx(0.0), m_dDy(0.0), m_dAngle(0.0) {}

    std::unique_ptr<Building> Building::createBuilding(BuildID id) {
        switch (id) {
            case arsenal:
                return std::unique_ptr<Building>(new ArsenalBuilding);
            case cannon:
                return std::unique_ptr<Building>(new CannonBuilding);
            case factory:
                return std::unique_ptr<Building>(new FactoryBuilding);
            case gen:
                return std::unique_ptr<Building>(new GeneratorBuilding);
            case lab:
                return std::unique_ptr<Building>(new LaboratoryBuilding);
            case main:
                return std::unique_ptr<Building>(new MainBaseBuilding);
            case mine:
                return std::unique_ptr<Building>(new MineBuilding);
            case nsilo:
                return std::unique_ptr<Building>(new NuclearSiloBuilding);
            case oil:
                return std::unique_ptr<Building>(new OilDerrickBuilding);
            default:
                assert(false);
        }
    }

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

    void Building::setSelected(bool value) {
        m_bSelected = value;
    }

    bool Building::isSelected() const {
        return m_bSelected;
    }

    sf::Sprite& Building::getSprite() {
        return m_aAnimation.getSprite();
    }
}