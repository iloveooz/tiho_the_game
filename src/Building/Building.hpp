#ifndef TIHO_BUILDING_HPP
#define TIHO_BUILDING_HPP

#include <string>
#include <cmath>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"
#include "../Animation/BuildingAnimation.hpp"
#include "../Cursor/Cursor.hpp"

namespace Buildings {
    enum class BuildID {
        nothing = 0,
        arsenal,
        cannon,
        factory,
        gen,
        lab,
        main,
        mine,
        nsilo,
        oil,
        count
    };

    enum class eRelationType {
        NOTHING,
        MINE,
        ALLY,
        ENEMY
    };

    class Building : public IObject {
    public:
        Building();
        virtual ~Building() {};

        static std::unique_ptr<Building> createBuilding(BuildID);

        void settings(Animations::BuildingAnimation &animation, double x, double y, double angle = 0);
        virtual void update();
        void draw(sf::RenderWindow &app);

        std::string& getName();

        sf::Sprite& getSprite();
        ControlGame::Cursor& getCursor();

        sf::Vector2f& getPosition();

        bool isAlive() const;
        void setDead();

        void setHealth(int value);

        void setSelected(bool value);
        bool isSelected() const;

        void setRelation(eRelationType type);
        eRelationType getRelation() const;

    protected:
        void setColor();

        // координаты фигуры
        sf::Vector2f m_position;

        // смещение
        double m_dDx;
        double m_dDy;

        // угол поворота
        double m_dAngle;

        // здоровье
        int m_iHealth;
        int m_iMaxHealth;
        bool m_bAlive;

        // выбран ли объект
        bool m_bSelected;

        // наименование элемента
        std::string m_sName;

        // анимация или спрайт
        Animations::BuildingAnimation m_aAnimation;

        ControlGame::Cursor m_cursor;
        sf::RectangleShape m_healthBar;

        eRelationType m_eRelationType;
    };
}
#endif //TIHO_BUILDING_HPP
