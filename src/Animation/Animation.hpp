#ifndef TIHO_ANIMATION_HPP
#define TIHO_ANIMATION_HPP

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

namespace Animations {

    enum class AnimationType {
        Empty = 0,
        CharacterAnim,
        BuildingAnim,
        MapAnim,
        ExplodeAnim,
        Count
    };

    class Animation : public IObject {
    public:
        Animation() {}
        virtual ~Animation() {}

        virtual void update();
        virtual sf::Sprite& getSprite() { return m_sprite; }

    protected:
        sf::Sprite m_sprite;
    };

}

#endif //TIHO_ANIMATION_HPP
