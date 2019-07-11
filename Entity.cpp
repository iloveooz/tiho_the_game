//
// Created by fahr on 24.01.19.
//

#include "Entity.h"

void Entity::settings(Animation &anim, double X, double Y, double Angle) {
    x = X;
    y = Y;
    angle = Angle;
    animation = anim;
}

void Entity::update() {}

void Entity::draw(sf::RenderWindow &app) {
    animation.sprite.setPosition((float )x, (float )y);
    animation.sprite.setRotation(angle + x);
    animation.sprite.setColor(sf::Color::Green);
    app.draw(animation.sprite);
}
