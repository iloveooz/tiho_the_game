#ifndef TIHO_BUILDINGANIMATION_HPP
#define TIHO_BUILDINGANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

namespace Animations {

    class BuildingAnimation : public Animation {
    public:
        BuildingAnimation();
        virtual ~BuildingAnimation();

        BuildingAnimation(sf::Texture &t, int wBorder, int hBorder);

        void setTexture(sf::Texture &t, int wBorder, int hBorder);

        sf::Sprite &getSprite();

    private:
        sf::Sprite m_sprite;
    };

}

#endif //TIHO_BUILDINGANIMATION_HPP
