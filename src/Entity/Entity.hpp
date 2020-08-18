#ifndef TIHO_ENTITY_HPP
#define TIHO_ENTITY_HPP

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../Animation/Animation.hpp"
#include "../IObject/IObject.hpp"

class Entity : public IObject {
public:
    Entity();
    virtual ~Entity() {};

    void settings (Animation &animation, double x, double y, double angle = 0);
    virtual void update();
    void draw(sf::RenderWindow &app);

    // координаты фигуры
    double m_dX;
    double m_dY;

    // смещение
    double m_dDx;
    double m_dDy;

    // угол поворота
    double m_dAngle;

    // здоровье
    bool m_bAlive = true;

    // наименование элемента
    std::string m_sName;

    // анимация или спрайт
    Animation m_aAnimation;
};

#endif //TIHO_ENTITY_HPP
