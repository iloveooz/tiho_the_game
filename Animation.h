#ifndef TIHO_ANIMATION_H
#define TIHO_ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>

class Animation {
public:
    sf::Sprite sprite;

    Animation () {}

    Animation (sf::Texture &t, int wBorder, int hBorder) {
        sprite.setTexture(t);
        sprite.setOrigin(wBorder / 2, hBorder / 2);
    }
};


#endif //TIHO_ANIMATION_H
