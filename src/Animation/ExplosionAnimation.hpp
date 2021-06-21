#ifndef TIHO_EXPLOSIONANIMATION_HPP
#define TIHO_EXPLOSIONANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

namespace Animations {

    class ExplosionAnimation : public Animation {
    public:
        ExplosionAnimation();
        virtual ~ExplosionAnimation();

        ExplosionAnimation(sf::Texture &t, int wBorder, int hBorder);

        void setTexture(sf::Texture &t, int wBorder, int hBorder);

        sf::Sprite &getSprite();

    private:
        sf::Sprite m_Sprite;
        std::vector<sf::IntRect> m_vFrames;

        double m_dFrame;
        double m_dSpeed;
    };

}

#endif //TIHO_EXPLOSIONANIMATION_HPP
