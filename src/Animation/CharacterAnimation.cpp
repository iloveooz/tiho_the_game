#include "CharacterAnimation.hpp"

namespace Animations {

    CharacterAnimation::CharacterAnimation() {}

    CharacterAnimation::~CharacterAnimation() {}

    CharacterAnimation::CharacterAnimation(sf::Texture &t, int wBorder, int hBorder) {
        m_sprite.setTexture(t);
        m_sprite.setOrigin(wBorder / 2, hBorder / 2);
    }

    void CharacterAnimation::setTexture(sf::Texture &t, int wBorder, int hBorder) {
        m_sprite.setTexture(t);
        m_sprite.setOrigin(wBorder / 2, hBorder / 2);
    }
}