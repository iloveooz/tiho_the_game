#ifndef TIHO_LOSTSTATE_HPP
#define TIHO_LOSTSTATE_HPP

#include "GameState.hpp"

namespace States {
    class LostState : public GameState {
    public:
        LostState(std::shared_ptr<Game> pGame) : GameState(pGame) {}
    };
}

#endif //TIHO_LOSTSTATE_HPP
