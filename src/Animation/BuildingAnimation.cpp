#include "BuildingAnimation.hpp"

namespace Animations {

    BuildingAnimation::BuildingAnimation() {}

    BuildingAnimation::~BuildingAnimation() {}

    BuildingAnimation::BuildingAnimation(sf::Texture &t, int wBorder, int hBorder) {
        m_sprite.setTexture(t);
        m_sprite.setOrigin(wBorder, hBorder);
    }

    void BuildingAnimation::setTexture(sf::Texture &t, int wBorder, int hBorder) {
        m_sprite.setTexture(t);
        m_sprite.setOrigin(wBorder, hBorder);
    }

    sf::Sprite& BuildingAnimation::getSprite() {
        return m_sprite;
    }
}