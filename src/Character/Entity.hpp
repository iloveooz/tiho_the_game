#ifndef TIHO_ENTITY_HPP
#define TIHO_ENTITY_HPP

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../Animation/CharacterAnimation.hpp"
#include "../IObject/IObject.hpp"
#include "../Map/Map.hpp"

const int Weight = 1920; // ширина главного окна
const int Height = 640;  // высота главного окна

class Entity : public IObject {
public:
    Entity();
    virtual ~Entity() {};

    void settings (Animations::Animation &animation, double x, double y, double angle = 0);
    virtual void update(double dx, double dy);
    void draw(sf::RenderWindow &app);

    void setName(const std::string& name);
    std::string& getName();

    bool isAlive() const;

    sf::Vector2f& getPosition();

    Animations::Animation& getAnimation();

protected:
    // координаты фигуры
    sf::Vector2f m_position;

    // смещение
    double m_dDx;
    double m_dDy;

    // угол поворота
    double m_dSpeed;
    double m_dAngle;

    // здоровье
    int m_iHealth;
    bool m_bAlive;

    // выбран ли объект
    bool m_bIsSelected;

    // наименование элемента
    std::string m_sName;

    // анимация или спрайт
    Animations::Animation m_aAnimation;

private:
    std::unique_ptr<World::Map> m_pMap;
};

#endif //TIHO_ENTITY_HPP
