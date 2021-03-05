#include "Game.hpp"
#include "../Character/Factory/CarFactory.hpp"
#include "../Character/Factory/TankFactory.hpp"

Game::Game() : m_window(sf::VideoMode(Weight, Height), "Tycho Planet") {
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    if (!m_tBackground.loadFromFile("images/tiles/terrain.png"))
        throw std::runtime_error("Unable to load the terrain texture file");

    if (!m_tCar.loadFromFile("images/characters/car.png"))
        throw std::runtime_error("Unable to load the terrain texture file");

    if (!m_tTank.loadFromFile("images/characters/tank.png"))
        throw std::runtime_error("Unable to load the terrain texture file");

    m_sBackground.setTexture(m_tBackground);

    m_animTank.setTexture(m_tTank, 74, 108);
    m_animCar.setTexture(m_tCar, 43, 45);
}

Game::~Game() {
}

void Game::run() {
    fillGameStates();
    changeGameState(States::Playing);

    createMap();
    createObjects();

    while (m_window.isOpen()) {
        processEvents();
        updateObjects();
        renderObjects();
    }
}

void Game::createObjects() {
    TankFactory tankFactory;
    CarFactory carFactory;

    std::unique_ptr<Entity> car = carFactory.createEntity();
    car->settings(m_animCar, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(car));

    std::unique_ptr<Entity> tank = tankFactory.createEntity();
    tank->settings(m_animTank, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(tank));
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
}

void Game::handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed) {

    sf::Vector2i position = sf::Mouse::getPosition(m_window);

    if (button == sf::Mouse::Right && isPressed)
        std::cout << "Right pressed! Coordinates: x = " << position.x << ", y = " << position.y << std::endl;
    else if (button == sf::Mouse::Right && !isPressed)
        std::cout << "Right released! Coordinates: x = " << position.x << ", y = " << position.y << std::endl;
    else if (button == sf::Mouse::Left && isPressed)
        std::cout << "Left pressed! Coordinates: x = " << position.x << ", y = " << position.y << std::endl;
    else if (button == sf::Mouse::Left && !isPressed)
        std::cout << "Left released! Coordinates: x = " << position.x << ", y = " << position.y << std::endl;
}

void Game::changeGameState(States::TypeState gameState) {
    m_pCurrentState = std::move(m_gameStates[gameState]);
}

void Game::fillGameStates() {
    m_gameStates[States::Menu] = std::make_unique<States::MenuState>(shared_from_this());
    m_gameStates[States::Playing] = std::make_unique<States::PlayingState>(shared_from_this());
    m_gameStates[States::Won] = std::make_unique<States::WonState>(shared_from_this());
    m_gameStates[States::Lost] = std::make_unique<States::LostState>(shared_from_this());
}

void Game::createMap() {
    m_map.loadLevel();
}
