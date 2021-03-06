#ifndef TIHO_BUILDING_HPP
#define TIHO_BUILDING_HPP

#include <string>
#include <cmath>
#include <cassert>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"
#include "../Animation/BuildingAnimation.hpp"

namespace Buildings {
    enum BuildID {
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

    class Building : public IObject {
    public:
        Building();
        virtual ~Building() {};

        static std::unique_ptr<Building> createBuilding(BuildID);

        void settings(Animations::BuildingAnimation &animation, double x, double y, double angle = 0);
        virtual void update(double dx, double dy);
        void draw(sf::RenderWindow &app);

        std::string& getName();
        sf::Sprite& getSprite();

        bool isAlive() const;

        void setSelected(bool value);
        bool isSelected() const;

    protected:
        // координаты фигуры
        double m_dX;
        double m_dY;

        // смещение
        double m_dDx;
        double m_dDy;

        // угол поворота
        double m_dAngle;

        // здоровье
        int m_iHealth;
        bool m_bAlive;

        // выбран ли объект
        bool m_bSelected;

        // наименование элемента
        std::string m_sName;

        // анимация или спрайт
        Animations::BuildingAnimation m_aAnimation;
    };
}
#endif //TIHO_BUILDING_HPP
