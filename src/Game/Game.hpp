#ifndef TIHO_GAME_HPP
#define TIHO_GAME_HPP

#include <array>
#include <cmath>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

#include "../Character/Entity.hpp"
#include "../Character/Factory/CharacterFactory.hpp"

#include "../Building/Building.hpp"

#include "../Animation/CharacterAnimation.hpp"
#include "../Animation/ExplosionAnimation.hpp"

#include "../TextureHolder/TextureHolder.hpp"

#include "GameState.hpp"
#include "MenuState.hpp"
#include "PlayingState.hpp"
#include "WonState.hpp"
#include "LostState.hpp"

#include "../Logger/ConsoleLogger.hpp"
#include "../Logger/FileLogger.hpp"
#include "../Logger/SocketLogger.hpp"
#include "../Cursor/Cursor.hpp"
#include "../Character/Commands/UnitCommandsManager.hxx"

class Game : public IObject, public std::enable_shared_from_this<Game> {
public:
    Game();
    Game(const Game&) = delete;
    Game& operator = (const Game&) = delete;
    ~Game();

    void run();

    std::shared_ptr<Logger> getConsoleLogger() const;
    std::shared_ptr<Logger> getFileLogger() const;

private:
    void prepareGame();

    void fillGameStates();
    void changeGameState(States::TypeState gameState);

    void createCharacter(Factory::CharID id, sf::Vector2f position);
    static void placeCharacter(Factory::CharID id, sf::Vector2f& position);

    static void setBuildingToGrid(Buildings::BuildID id, sf::Vector2f& position);
    void showTemplateOfBuilding();
    void createBuilding(Buildings::BuildID id, sf::Vector2f position);
    void destroyBuilding();
    void explodeBuilding(sf::Vector2f position);

    void selectObjectOnMap();

    void createMap();

    void centerViewOfMap();
    void updateViewOfMap();

    void renderObjects();

    void processEvents();

    void handlePlayerKeyboardEvent(sf::Keyboard::Key key, bool isPressed);
    void handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed);
    void handlePlayerMouseWheelEvent(sf::Event& event);

    void checkMousePosition();

    World::Map& getMap();

    sf::RenderWindow m_window;

    std::vector<std::unique_ptr<Entity>> m_characters;
    Commands::UnitCommandsManager m_comManager;

    std::vector<std::unique_ptr<Buildings::Building>> m_buildings;

    ControlGame::Cursor m_cursor;

    std::shared_ptr<States::GameState> m_pCurrentState;
    std::array<std::unique_ptr<States::GameState>, static_cast<int>(States::TypeState::Count)> m_gameStates;

    Textures::TextureHolder m_textureHolder;

    sf::Sprite m_sBackground;

    std::map<Factory::CharID, Animations::CharacterAnimation> m_CharAnimap;

    Animations::CharacterAnimation m_animTank;
    Animations::CharacterAnimation m_animCar;
    Animations::CharacterAnimation m_animSpitFire;
    Animations::CharacterAnimation m_animNuke;
    Animations::CharacterAnimation m_animWorker;

    std::map<Buildings::BuildID, Animations::BuildingAnimation> m_BuildAnimap;

    Animations::BuildingAnimation m_animArsenal;
    Animations::BuildingAnimation m_animCannon;
    Animations::BuildingAnimation m_animFactory;
    Animations::BuildingAnimation m_animGenerator;
    Animations::BuildingAnimation m_animLab;
    Animations::BuildingAnimation m_animMain;
    Animations::BuildingAnimation m_animMine;
    Animations::BuildingAnimation m_animNSilo;
    Animations::BuildingAnimation m_animOil;

    std::map<Animations::ExplodeType, Animations::ExplosionAnimation> m_ExplodeAnimap;

    Animations::ExplosionAnimation m_animSmallExpl;
    Animations::ExplosionAnimation m_animMiddleExpl;
    Animations::ExplosionAnimation m_animBigExpl;

    sf::Sprite m_fakeBuilding;

    bool m_isViewMovingUp;
    bool m_isViewMovingDown;
    bool m_isViewMovingLeft;
    bool m_isViewMovingRight;

    bool m_isViewZoomingIn;
    bool m_isViewZoomingOut;

    World::Map m_map;

    sf::View m_camera;

    std::shared_ptr<Logger> m_consoleLogger;
    std::shared_ptr<Logger> m_fileLogger;

    long m_amountTanks;

    enum class eKeyPressed {
        empty = 0,
        WPressed,
        CPressed,
        TPressed,
        SPressed,
        RPressed
    } m_ePressedProperty;

    bool m_bBPressed;
    bool m_bDPressed;
    bool m_bDDPressed;

    Buildings::BuildID m_BuildingChoosen;
};

#endif //TIHO_GAME_HPP
