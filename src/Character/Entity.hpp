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
const int Height = 1080;  // высота главного окна

const double PI = 3.14159265;
const double angleAdjust = 270;

enum class eRelationType {
    NOTHING,
    MINE,
    ALLY,
    ENEMY
};

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

    void setRelation(eRelationType type);
    eRelationType getRelation() const;

    void setTarget(bool value);
    bool getTarget() const;

    int getDamage() const;

    bool isMoving() const;

    sf::Vector2f& getPosition();

    Animations::Animation& getAnimation();

    virtual void doGo(sf::Vector2f& position);
    virtual void doStop(sf::Vector2f& position);
    virtual void doPatrol(sf::Vector2f& position);
    virtual void doHold(sf::Vector2f& position);

protected:
    void setAngle();
    void setColor();
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
    int m_iMaxHealth;
    bool m_bAlive;

    // выбран ли объект
    bool m_bSelected;

    // цель для атаки
    bool m_bIsTarget;

    // наносимый урон
    int m_iDamage;

    enum class eMovingType {
        NO_MOVE,
        MOVING,
        PATROLLING,
        HOLDING
    } m_eMovingType;

    enum class eRadiusType {
        empty,      // = 0, неатакующий юнит
        close,      // = 1, рабочий
        small,      // = 2, машинка
        middle,     // = 3, пожарка
        far,        // = 5, танк
        huge,       // = 9, ракетница
        anyplace,   // = no, ядерная ракета
        count       // all
    } m_eRadiusType;

    eRelationType m_eRelationType;

    // наименование элемента
    std::string m_sName;

    // анимация или спрайт
    Animations::Animation m_aAnimation;

    ControlGame::Cursor m_cursor;
    sf::RectangleShape m_healthBar;

private:
    std::unique_ptr<World::Map> m_pMap;
};

#endif //TIHO_ENTITY_HPP
