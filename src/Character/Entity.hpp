#ifndef TIHO_ENTITY_HPP
#define TIHO_ENTITY_HPP

#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "../Animation/CharacterAnimation.hpp"
#include "../IObject/IObject.hpp"
#include "../Map/Map.hpp"
#include "../Cursor/Cursor.hpp"

const int Weight = 1920; // ширина главного окна
const int Height = 640;  // высота главного окна

const double PI = 3.14159265;
const double angleAdjust = 270;

class Entity : public IObject {
public:
    Entity();
    virtual ~Entity() {};

    void settings (Animations::Animation &animation, double x, double y, double angle = 0);
    virtual void update();
    void draw(sf::RenderWindow &app);

    void setName(const std::string& name);
    std::string& getName();

    sf::Sprite& getSprite();
    ControlGame::Cursor& getCursor();

    void setDead();
    bool isAlive() const;

    void setSelected(bool value);
    bool isSelected() const;

    bool isMoving() const;

    sf::Vector2f& getPosition();

    Animations::Animation& getAnimation();

    virtual void doGo(sf::Vector2f& position);
    virtual void doStop(sf::Vector2f& position);
    virtual void doPatrol(sf::Vector2f& position);

protected:
    void setAngle();
    // координаты фигуры
    sf::Vector2f m_position;
    sf::Vector2f m_beginPosition;
    sf::Vector2f m_targetPosition;

    // смещение
    double m_dDx;
    double m_dDy;

    // угол поворота
    double m_dAngle;

    double m_dRadius;

    // скорость юнита
    double m_dSpeed;

    // здоровье
    int m_iHealth;
    bool m_bAlive;

    // выбран ли объект
    bool m_bSelected;

    enum class eMovingType {
        NO_MOVE,
        MOVING,
        PATROLLING
    } m_eMovingType;

    // наименование элемента
    std::string m_sName;

    // анимация или спрайт
    Animations::Animation m_aAnimation;

    ControlGame::Cursor m_cursor;

private:
    std::unique_ptr<World::Map> m_pMap;
};

#endif //TIHO_ENTITY_HPP
