#ifndef TIHO_ANIMATION_HPP
#define TIHO_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

class Animation {
public:
    Animation();
    Animation(sf::Texture &t, int wBorder, int hBorder);

    sf::Sprite& getSprite();
private:
    sf::Sprite m_sprite;
};

#endif //TIHO_ANIMATION_HPP
