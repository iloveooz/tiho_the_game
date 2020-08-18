#ifndef TIHO_ENTITY_HPP
#define TIHO_ENTITY_HPP

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../Animation/Animation.hpp"
#include "../IObject/IObject.hpp"

class Entity : public IObject {
public:
    // координаты фигуры
    double x;
    double y;

    // смещение
    double dx;
    double dy;

    // угол поворота
    double angle;

    // здоровье
    bool alive = true;
    int hp;

    // наименование элемента
    std::string name;

    // анимация или спрайт
    Animation animation;

    // конструктор
    Entity () {
        alive = true;
        hp = 100;
    }

    // установки при создании объекта
    void settings (Animation &anim, double X, double Y, double Angle = 0);

    // передвижение
    virtual void update();

    void draw(sf::RenderWindow &app);

    virtual ~Entity() = default;
};


#endif //TIHO_ENTITY_HPP
