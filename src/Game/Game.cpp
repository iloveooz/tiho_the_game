#include "Game.hpp"
#include "../Character/Factory/CarFactory.hpp"
#include "../Character/Factory/TankFactory.hpp"

Game::Game() :
        m_window(sf::VideoMode(Weight, Height), "Tycho Planet"),
        m_consoleLogger(new ConsoleLogger()),
        m_fileLogger(new FileLogger("output.log")) {

    m_consoleLogger->log("Game", "Game", "BEGIN");
    m_fileLogger->log("Game", "Game", "BEGIN");

    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    m_textureHolder.init();

    m_sBackground.setTexture(m_textureHolder.get(Textures::Terrain));
    m_animTank.setTexture(m_textureHolder.get(Textures::Tank), 108, 108);
    m_animCar.setTexture(m_textureHolder.get(Textures::Car), 45, 45);

    m_fileLogger->log("Game", "Game", "END");
}

Game::~Game() {
}

void Game::run() {
    m_fileLogger->log("Game", "run", "BEGIN");

    fillGameStates();
    changeGameState(States::Playing);

    createMap();
    createObjects();

    while (m_window.isOpen()) {
        processEvents();
        updateObjects();
        renderObjects();
    }

    m_fileLogger->log("Game", "run", "END");
}

void Game::createObjects() {
    m_fileLogger->log("Game", "createObjects", "BEGIN");

    TankFactory tankFactory;
    CarFactory carFactory;

    std::unique_ptr<Entity> car = carFactory.createEntity();
    car->settings(m_animCar, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(car));

    std::unique_ptr<Entity> tank = tankFactory.createEntity();
    tank->settings(m_animTank, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(tank));

    m_fileLogger->log("Game", "createObjects", "END");
}

void Game::updateObjects() {
    double dx = 0.0, dy = 0.0;
    // цикл обновления
    for (auto &object : m_objects) {
        if (m_isMovingUp)
            dy -= 1.0;
        if (m_isMovingDown)
            dy += 1.0;
        if (m_isMovingLeft)
            dx -= 1.0;
        if (m_isMovingRight)
            dx += 1.0;

        object->update(dx, dy);

        if (!object->isAlive()) {
            m_objects.remove(object);
        }
    }
}

void Game::renderObjects() {
    m_window.clear();

    m_window.draw(m_map);

    // отображение объектов
    for (auto const &object : m_objects)
        object->draw(m_window);

    m_window.display();
}

void Game::processEvents() {
    sf::Event event;

    // обработка пользовательского ввода
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::KeyPressed:
                handlePlayerKeyboardEvent(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerKeyboardEvent(event.key.code, false);
                break;
            case sf::Event::MouseButtonPressed:
                handlePlayerMouseEvent(event.mouseButton.button, true);
                break;
            case sf::Event::MouseButtonReleased:
                handlePlayerMouseEvent(event.mouseButton.button, false);
                break;
        }
    }
}

void Game::handlePlayerKeyboardEvent(sf::Keyboard::Key key, bool isPressed) {
    m_fileLogger->log("Game", "handlePlayerKeyboardEvent", "BEGIN");

    if (key == sf::Keyboard::Up)
        m_isMovingUp = isPressed;
    else if (key == sf::Keyboard::Down)
        m_isMovingDown = isPressed;
    else if (key == sf::Keyboard::Left)
        m_isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        m_isMovingRight = isPressed;
    else if (key == sf::Keyboard::B && isPressed)
        createObjects();

    m_fileLogger->log("Game", "handlePlayerKeyboardEvent", "END");
}

void Game::handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed) {
    m_fileLogger->log("Game", "handlePlayerMouseEvent", "BEGIN");

    sf::Vector2i position = sf::Mouse::getPosition(m_window);

    if (button == sf::Mouse::Right && isPressed)
        m_consoleLogger->log("Game", "handlePlayerMouseEvent", "Right pressed! Coordinates: x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y));
    else if (button == sf::Mouse::Right && !isPressed)
        m_consoleLogger->log("Game", "handlePlayerMouseEvent", "Right released! Coordinates: x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y));
    else if (button == sf::Mouse::Left && isPressed)
        m_consoleLogger->log("Game", "handlePlayerMouseEvent", "Left pressed! Coordinates: x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y));
    else if (button == sf::Mouse::Left && !isPressed)
        m_consoleLogger->log("Game", "handlePlayerMouseEvent", "Left released! Coordinates: x = " + std::to_string(position.x) + ", y = " + std::to_string(position.y));

    m_fileLogger->log("Game", "handlePlayerMouseEvent", "END");
}

void Game::changeGameState(States::TypeState gameState) {
    m_fileLogger->log("Game", "changeGameState", "BEGIN");

    m_pCurrentState = std::move(m_gameStates[gameState]);

    m_fileLogger->log("Game", "changeGameState", "END");
}

void Game::fillGameStates() {
    m_fileLogger->log("Game", "fillGameStates", "BEGIN");

    m_gameStates[States::Menu] = std::make_unique<States::MenuState>(shared_from_this());
    m_gameStates[States::Playing] = std::make_unique<States::PlayingState>(shared_from_this());
    m_gameStates[States::Won] = std::make_unique<States::WonState>(shared_from_this());
    m_gameStates[States::Lost] = std::make_unique<States::LostState>(shared_from_this());

    m_fileLogger->log("Game", "fillGameStates", "END");
}

void Game::createMap() {
    m_fileLogger->log("Game", "createMap", "BEGIN");

    m_map.loadLevel(m_textureHolder);

    m_fileLogger->log("Game", "createMap", "END");
}

std::shared_ptr<Logger> Game::getConsoleLogger() const {
    return m_consoleLogger;
}

std::shared_ptr<Logger> Game::getFileLogger() const {
    return m_fileLogger;
}