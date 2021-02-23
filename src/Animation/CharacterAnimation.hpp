#ifndef TIHO_CHARACTERANIMATION_HPP
#define TIHO_CHARACTERANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

namespace Animations {

    class CharacterAnimation : public Animation {
    public:
        CharacterAnimation();

        CharacterAnimation(sf::Texture &t, int wBorder, int hBorder);

        void setTexture(sf::Texture &t, int wBorder, int hBorder);

        sf::Sprite &getSprite();

    private:
        sf::Sprite m_sprite;
    };

}

#endif //TIHO_CHARACTERANIMATION_HPP
