#ifndef TIHO_WONSTATE_HPP
#define TIHO_WONSTATE_HPP

#include "GameState.hpp"

namespace States {
    class WonState : public GameState {
    public:
        WonState(std::shared_ptr<Game> pGame) : GameState(pGame) {}
    };
}

#endif //TIHO_WONSTATE_HPP
