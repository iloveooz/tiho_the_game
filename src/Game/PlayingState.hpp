#ifndef TIHO_PLAYINGSTATE_HPP
#define TIHO_PLAYINGSTATE_HPP

#include "GameState.hpp"

namespace States {
    class PlayingState : public GameState {
    public:
        PlayingState(std::shared_ptr<Game> pGame) : GameState(pGame) {}
    };
}

#endif //TIHO_PLAYINGSTATE_HPP
