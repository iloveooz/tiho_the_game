#include "Entity.hpp"

void Entity::settings(Animation &anim, double X, double Y, double Angle) {
    x = X;
    y = Y;
    angle = Angle;
    animation = anim;
}

void Entity::update() {}

void Entity::draw(sf::RenderWindow &app) {
    animation.getSprite().setPosition((float )x, (float )y);
    animation.getSprite().setRotation(angle + x);
    animation.getSprite().setColor(sf::Color::Green);
    app.draw(animation.getSprite());
}
