#ifndef TIHO_ANIMATION_HPP
#define TIHO_ANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "../IObject/IObject.hpp"

class Animation : public IObject {
public:
    Animation();
    Animation(sf::Texture &t, int wBorder, int hBorder);

    void setTexture(sf::Texture &t, int wBorder, int hBorder);

    sf::Sprite& getSprite();
private:
    sf::Sprite m_sprite;
};

#endif //TIHO_ANIMATION_HPP
