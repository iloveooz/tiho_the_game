#ifndef TIHO_BUILDING_HPP
#define TIHO_BUILDING_HPP

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../Animation/Animation.hpp"
#include "../IObject/IObject.hpp"

class Building : public IObject {
public:
    Building();
    virtual ~Building() {};

    void settings (Animation &animation, double x, double y, double angle = 0);
    virtual void update(double dx, double dy);
    void draw(sf::RenderWindow &app);

    std::string& getName();
    bool isAlive() const;

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

    // наименование элемента
    std::string m_sName;

    // анимация или спрайт
    Animation m_aAnimation;
};

#endif //TIHO_BUILDING_HPP