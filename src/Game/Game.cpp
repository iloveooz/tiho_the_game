#include "Game.hpp"
#include "../Factory/CarFactory.hpp"
#include "../Factory/TankFactory.hpp"

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

    std::unique_ptr<Entity> tank = tankFactory.createEntity();
    tank->settings(m_animTank, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(tank));

    std::unique_ptr<Entity> car = carFactory.createEntity();
    car->settings(m_animCar, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(car));
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

    m_window.draw(m_sBackground);

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
                handlePlayerEvent(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerEvent(event.key.code, false);
                break;
        }
    }
}

void Game::handlePlayerEvent(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Up)
        m_isMovingUp = isPressed;
    else if (key == sf::Keyboard::Down)
        m_isMovingDown = isPressed;
    else if (key == sf::Keyboard::Left)
        m_isMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        m_isMovingRight = isPressed;
}