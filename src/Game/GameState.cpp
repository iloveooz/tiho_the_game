#include "GameState.hpp"

#include <utility>

namespace States {

    GameState::GameState(std::shared_ptr<Game> pGame) : m_pGame(std::move(pGame)) {}

    std::shared_ptr<Game> GameState::getGame() const {
        return m_pGame;
    }

}