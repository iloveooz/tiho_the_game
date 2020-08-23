#include "Game.hpp"

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
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        m_window.clear();
        m_window.draw(m_sBackground);

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

        // отображение танков
        for (auto i : m_objects)
            i->draw(m_window);

        m_window.display();
    }
}

void Game::createObjects() {
    for (int i = 0; i < m_amountTanks; i++) {
        Tank *tank = new Tank();
        Car *car = new Car();

        tank->settings(m_animTank, rand() % Weight, rand() % Height, rand() % 360);
        car->settings(m_animCar, rand() % Weight, rand() % Height, rand() % 360);

        // вставка элемента в конец контейнера
        m_objects.push_back(tank);
        m_objects.push_back(car);
    }
}
