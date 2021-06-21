#include "ExplosionAnimation.hpp"

namespace Animations {
    ExplosionAnimation::ExplosionAnimation() {}

    ExplosionAnimation::~ExplosionAnimation() {}

    ExplosionAnimation::ExplosionAnimation(sf::Texture &t, int wBorder, int hBorder) {
        m_Sprite.setTexture(t);
        m_Sprite.setOrigin(wBorder / 2, hBorder / 2);
    }

    void ExplosionAnimation::setTexture(sf::Texture &t, int wBorder, int hBorder) {
        m_Sprite.setTexture(t);
        m_Sprite.setOrigin(wBorder / 2, hBorder / 2);
    }

    sf::Sprite& ExplosionAnimation::getSprite() {
        return m_Sprite;
    }
}