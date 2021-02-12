#ifndef TIHO_MENUSTATE_HPP
#define TIHO_MENUSTATE_HPP

#include "GameState.hpp"

namespace States {
    class MenuState : public GameState {
    public:
        MenuState(std::shared_ptr<Game> pGame) : GameState(pGame) {}

    };
}

#endif //TIHO_MENUSTATE_HPP
