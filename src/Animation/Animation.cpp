#include "Animation.hpp"

Animation::Animation() {}

Animation::Animation(sf::Texture &t, int wBorder, int hBorder) {
    m_sprite.setTexture(t);
    m_sprite.setOrigin(wBorder / 2, hBorder / 2);
}

sf::Sprite& Animation::getSprite() {
    return m_sprite;
}
