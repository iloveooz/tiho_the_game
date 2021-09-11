#ifndef TIHO_EXPLOSIONANIMATION_HPP
#define TIHO_EXPLOSIONANIMATION_HPP

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"

namespace Animations {

    enum class ExplodeType {
        Empty = 0,
        SmallExplode,   // for battle
        MiddleExplode,  // for units
        BigExplode,     // for buildings
        Count
    };

    class ExplosionAnimation : public Animation {
    public:
        ExplosionAnimation();
        virtual ~ExplosionAnimation();

        ExplosionAnimation(sf::Texture &t, int wBorder, int hBorder);

        void setTexture(sf::Texture &t, ExplodeType type);
    };

}

#endif //TIHO_EXPLOSIONANIMATION_HPP
