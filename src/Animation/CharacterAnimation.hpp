#ifndef TIHO_CHARACTERANIMATION_HPP
#define TIHO_CHARACTERANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

namespace Animations {

    class CharacterAnimation : public Animation {
    public:
        CharacterAnimation();
        virtual ~CharacterAnimation();

        CharacterAnimation(sf::Texture &t, int wBorder, int hBorder);

        void setTexture(sf::Texture &t, int wBorder, int hBorder);
    };

}

#endif //TIHO_CHARACTERANIMATION_HPP
