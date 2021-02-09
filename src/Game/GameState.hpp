#ifndef TIHO_GAMESTATE_HPP
#define TIHO_GAMESTATE_HPP

#include <memory>

#include "../IObject/IObject.hpp"

#include "Game.hpp"

namespace States {

    enum State {
        Menu,
        Playing,
        Won,
        Lost
    };

    class GameState : public IObject {
    public:

    private:
        std::unique_ptr<Game> m_pGame;
    };
}
#endif //TIHO_GAMESTATE_HPP
