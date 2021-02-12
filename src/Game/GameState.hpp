#ifndef TIHO_GAMESTATE_HPP
#define TIHO_GAMESTATE_HPP

#include <memory>

#include "../IObject/IObject.hpp"

class Game;

namespace States {

    enum TypeState {
        Menu,
        Playing,
        Won,
        Lost,
        Count
    };

    class GameState : public IObject {
    public:
        GameState(std::shared_ptr<Game> pGame);
        std::shared_ptr<Game> getGame() const;

    private:
        std::shared_ptr<Game> m_pGame;
    };
}
#endif //TIHO_GAMESTATE_HPP
