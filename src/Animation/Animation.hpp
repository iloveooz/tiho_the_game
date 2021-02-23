#ifndef TIHO_ANIMATION_HPP
#define TIHO_ANIMATION_HPP

#include "../IObject/IObject.hpp"

namespace Animations {

    enum AnimationType {
        NothingAnim,
        CharacterAnim,
        BuildingAnim,
        Count
    };

    class Animation : public IObject {

    };

}

#endif //TIHO_ANIMATION_HPP
