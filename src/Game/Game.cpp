#include "Game.hpp"

#include <memory>

#include "../Character/Factory/CharacterFactory.hpp"

Game::Game() :
        m_window(sf::VideoMode(Weight, Height), "Tycho Planet"),
        m_consoleLogger(new ConsoleLogger()),
        m_fileLogger(new FileLogger("output.log")) {

    m_fileLogger->log("Game", "Game", "BEGIN");

    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    m_textureHolder.init();

    m_sBackground.setTexture(m_textureHolder.get(Textures::Terrain));

    m_animTank.setTexture(m_textureHolder.get(Textures::Tank), 108, 108);
    m_animCar.setTexture(m_textureHolder.get(Textures::Car), 45, 45);
    m_animSpitFire.setTexture(m_textureHolder.get(Textures::SpitFire), 48, 48);
    m_animNuke.setTexture(m_textureHolder.get(Textures::NuclearRocket), 48, 48);
    m_animWorker.setTexture(m_textureHolder.get(Textures::Worker), 54, 54);

    m_animArsenal.setTexture(m_textureHolder.get(Textures::Arsenal), 64, 64);
    m_animCannon.setTexture(m_textureHolder.get(Textures::Cannon), 64, 64);
    m_animFactory.setTexture(m_textureHolder.get(Textures::Factory), 128, 64);
    m_animGenerator.setTexture(m_textureHolder.get(Textures::Generator), 64, 64);
    m_animLab.setTexture(m_textureHolder.get(Textures::Laboratory), 64, 64);
    m_animMain.setTexture(m_textureHolder.get(Textures::MainBase), 128, 128);
    m_animMine.setTexture(m_textureHolder.get(Textures::Mine), 64, 64);
    m_animNSilo.setTexture(m_textureHolder.get(Textures::NuclearSilo), 64, 64);
    m_animOil.setTexture(m_textureHolder.get(Textures::OilDerrick), 64, 64);

    m_fileLogger->log("Game", "Game", "END");
}

Game::~Game() {
}

void Game::run() {
    m_fileLogger->log("Game", "run", "BEGIN");

    fillGameStates();
    changeGameState(States::Playing);

    createMap();
    //createObjects();
    //createBuildings();

    while (m_window.isOpen()) {
        processEvents();
        updateObjects();
        renderObjects();
    }

    m_fileLogger->log("Game", "run", "END");
}

void Game::createObjects() {
    m_fileLogger->log("Game", "createObjects", "BEGIN");

    Factory::CharacterFactory factory;

    std::unique_ptr<Entity> car = factory.createEntity(Factory::CharID::car);
    car->settings(m_animCar, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(car));

    std::unique_ptr<Entity> tank = factory.createEntity(Factory::CharID::tank);
    tank->settings(m_animTank, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(tank));

    std::unique_ptr<Entity> spitfire = factory.createEntity(Factory::CharID::spit);
    spitfire->settings(m_animSpitFire, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(spitfire));

    std::unique_ptr<Entity> nuke = factory.createEntity(Factory::CharID::nuke);
    nuke->settings(m_animNuke, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(nuke));

    std::unique_ptr<Entity> worker = factory.createEntity(Factory::CharID::work);
    worker->settings(m_animWorker, rand() % Weight, rand() % Height, 0);
    m_objects.push_back(std::move(worker));

    m_fileLogger->log("Game", "createObjects", "END");
}

void Game::createBuildings() {
    m_fileLogger->log("Game", "createBuildings", "BEGIN");

    std::unique_ptr<Buildings::Building> arsenal = Buildings::Building::createBuilding(Buildings::arsenal);
    arsenal->settings(m_animArsenal, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(arsenal));

    std::unique_ptr<Buildings::Building> cannon = Buildings::Building::createBuilding(Buildings::cannon);
    cannon->settings(m_animCannon, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(cannon));

    std::unique_ptr<Buildings::Building> factory = Buildings::Building::createBuilding(Buildings::factory);
    factory->settings(m_animFactory, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(factory));

    std::unique_ptr<Buildings::Building> generator = Buildings::Building::createBuilding(Buildings::gen);
    generator->settings(m_animGenerator, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(generator));

    std::unique_ptr<Buildings::Building> laboratory = Buildings::Building::createBuilding(Buildings::lab);
    laboratory->settings(m_animLab, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(laboratory));

    std::unique_ptr<Buildings::Building> main = Buildings::Building::createBuilding(Buildings::main);
    main->settings(m_animMain, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(main));

    std::unique_ptr<Buildings::Building> mine = Buildings::Building::createBuilding(Buildings::mine);
    mine->settings(m_animMine, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(mine));

    std::unique_ptr<Buildings::Building> nsilo = Buildings::Building::createBuilding(Buildings::nsilo);
    nsilo->settings(m_animNSilo, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(nsilo));

    std::unique_ptr<Buildings::Building> oilderrick = Buildings::Building::createBuilding(Buildings::oil);
    oilderrick->settings(m_animOil, rand() % Weight, rand() % Height, 0);
    m_buildings.push_back(std::move(oilderrick));

    m_fileLogger->log("Game", "createBuildings", "END");
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

    for (auto const &object : m_buildings)
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
    else if (key == sf::Keyboard::B && isPressed) {
        createObjects();
    }

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