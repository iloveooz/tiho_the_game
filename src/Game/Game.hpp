#ifndef TIHO_GAME_HPP
#define TIHO_GAME_HPP

#include <array>
#include <cmath>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

#include "../Character/Entity.hpp"
#include "../Character/Car.hpp"
#include "../Character/Tank.hpp"

#include "../Animation/CharacterAnimation.hpp"

#include "../TextureHolder/TextureHolder.hpp"

#include "GameState.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "WonState.hpp"
#include "LostState.hpp"

#include "../Logger/ConsoleLogger.hpp"
#include "../Logger/FileLogger.hpp"
#include "../Logger/SocketLogger.hpp"

namespace States {
    class GameState;
}

class Game : public IObject, public std::enable_shared_from_this<Game> {
public:
    Game();
    ~Game();

    void run();

    sf::Texture& getBackground() const;
    sf::Texture& getCarTexture() const;
    sf::Texture& getTankTexture() const;

    void fillGameStates();
    void changeGameState(States::TypeState gameState);

private:
    void createObjects();
    void createMap();

    void updateObjects();
    void renderObjects();

    void processEvents();

    void handlePlayerKeyboardEvent(sf::Keyboard::Key key, bool isPressed);
    void handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed);

    sf::RenderWindow m_window;
    std::list<std::unique_ptr<Entity>> m_objects;

    std::shared_ptr<States::GameState> m_pCurrentState;
    std::array<std::unique_ptr<States::GameState>, States::TypeState::Count> m_gameStates;

    Textures::TextureHolder m_textureHolder;

    sf::Sprite m_sBackground;

    Animations::CharacterAnimation m_animTank;
    Animations::CharacterAnimation m_animCar;

    bool m_isMovingUp;
    bool m_isMovingDown;
    bool m_isMovingLeft;
    bool m_isMovingRight;

    World::Map m_map;

    std::shared_ptr<Logger> m_consoleLogger;
    std::shared_ptr<Logger> m_fileLogger;
    std::shared_ptr<Logger> m_socketLogger;

    long m_amountTanks;
};

#endif //TIHO_GAME_HPP
