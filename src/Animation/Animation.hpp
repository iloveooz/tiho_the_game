#ifndef TIHO_ANIMATION_HPP
#define TIHO_ANIMATION_HPP

#include "../IObject/IObject.hpp"

namespace Animations {

    enum AnimationType {
        NothingAnim,
        CharacterAnim,
        BuildingAnim,
        MapAnim,
        Count
    };

    class Animation : public IObject {
    public:
        Animation() {}
        virtual ~Animation() {}
    };

}

#endif //TIHO_ANIMATION_HPP
