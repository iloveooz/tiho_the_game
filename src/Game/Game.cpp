#include "Game.hpp"
#include "../Factory/CarFactory.hpp"
#include "../Factory/TankFactory.hpp"

Game::Game() : m_window(sf::VideoMode(Weight, Height), "Tycho Planet") {
    m_window.setFramerateLimit(60);

    m_amountTanks = 5;

    if (!m_tBackground.loadFromFile("images/terrain.png"))
        throw std::runtime_error("Unable to load the terrain texture file");

    if (!m_tCar.loadFromFile("images/car.png"))
        throw std::runtime_error("Unable to load the terrain texture file");

    if (!m_tTank.loadFromFile("images/tank.png"))
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

    Entity *tank = tankFactory.createEntity();
    tank->settings(m_animTank, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(tank);

    Entity *car = carFactory.createEntity();
    car->settings(m_animCar, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(car);
}

void Game::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void Game::updateObjects() {
    // цикл обновления
    for (auto i = m_objects.begin(); i != m_objects.end();) {
        Entity *object = *i;
        object->update();

        if (!object->isAlive()) {
            i = m_objects.erase(i);
            delete object;
        }
        else
            i++;
    }
}

void Game::renderObjects() {
    m_window.clear();
    m_window.draw(m_sBackground);

    // отображение объектов
    for (auto i : m_objects)
        i->draw(m_window);

    m_window.display();
}