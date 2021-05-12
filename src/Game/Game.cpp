#include "Game.hpp"

#include <memory>

#include "../Character/Factory/CharacterFactory.hpp"

Game::Game() :
        m_window(sf::VideoMode(Weight, Height), "Tycho Planet", sf::Style::Fullscreen),
        m_consoleLogger(new ConsoleLogger()),
        m_fileLogger(new FileLogger("output.log")) {

    m_fileLogger->log("Game", "Game", "BEGIN");

    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    m_camera.setSize(sf::Vector2f(Weight, Height));
    m_camera.setCenter(sf::Vector2f(Weight / 2, Height / 2));

    m_textureHolder.init();

    m_sBackground.setTexture(m_textureHolder.get(Textures::Terrain));

    m_animTank.setTexture(m_textureHolder.get(Textures::Tank), 108, 108);
    m_animCar.setTexture(m_textureHolder.get(Textures::Car), 45, 45);
    m_animSpitFire.setTexture(m_textureHolder.get(Textures::SpitFire), 48, 48);
    m_animNuke.setTexture(m_textureHolder.get(Textures::NuclearRocket), 48, 48);
    m_animWorker.setTexture(m_textureHolder.get(Textures::Worker), 54, 54);


    m_animArsenal.setTexture(m_textureHolder.get(Textures::Arsenal), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::arsenal, m_animArsenal));

    m_animCannon.setTexture(m_textureHolder.get(Textures::Cannon), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::cannon, m_animCannon));

    m_animFactory.setTexture(m_textureHolder.get(Textures::Factory), 128, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::factory, m_animFactory));

    m_animGenerator.setTexture(m_textureHolder.get(Textures::Generator), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::gen, m_animGenerator));

    m_animLab.setTexture(m_textureHolder.get(Textures::Laboratory), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::lab, m_animLab));

    m_animMain.setTexture(m_textureHolder.get(Textures::MainBase), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::main, m_animMain));

    m_animMine.setTexture(m_textureHolder.get(Textures::Mine), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::mine, m_animMine));

    m_animNSilo.setTexture(m_textureHolder.get(Textures::NuclearSilo), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::nsilo, m_animNSilo));

    m_animOil.setTexture(m_textureHolder.get(Textures::OilDerrick), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::oil, m_animOil));

    m_fileLogger->log("Game", "Game", "END");
}

Game::~Game() {
}

void Game::run() {
    m_fileLogger->log("Game", "run", "BEGIN");

    fillGameStates();
    changeGameState(States::Playing);

    createMap();

    while (m_window.isOpen()) {
        checkMousePosition();
        processEvents();
        updateViewOfMap();
        renderObjects();
    }

    m_fileLogger->log("Game", "run", "END");
}

void Game::createCharacter() {
    m_fileLogger->log("Game", "createCharacter", "BEGIN");

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

    m_fileLogger->log("Game", "createCharacter", "END");
}

void Game::createBuilding(Buildings::BuildID id, sf::Vector2f position) {
    m_fileLogger->log("Game", "createBuilding", "BEGIN");

    std::unique_ptr<Buildings::Building> building = Buildings::Building::createBuilding(id);
    building->settings(m_BuildAnimap.find(id)->second, position.x, position.y, 0);
    m_buildings.push_back(std::move(building));

    m_fileLogger->log("Game", "createBuilding", "END");
}

void Game::checkMousePosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
    // m_consoleLogger->log("Game", "checkMousePosition", "x = " + std::to_string(mousePosition.x) + ", y = " + std::to_string(mousePosition.y));

    m_isViewMovingLeft = (mousePosition.x < 3);
    m_isViewMovingRight = (mousePosition.x > m_window.getSize().x - 3);
    m_isViewMovingUp = (mousePosition.y < 3);
    m_isViewMovingDown = (mousePosition.y > m_window.getSize().y - 3);
}

void Game::updateViewOfMap() {
    double dx = 0.0, dy = 0.0, zf = 1.0;

    if (m_isViewMovingUp && m_camera.getCenter().y > int(Height / 2))
        dy -= 50.0;
    if (m_isViewMovingDown && m_camera.getCenter().y < m_map.getMapSize().y * 128 - int(Height / 2) - 50)
        dy += 50.0;
    if (m_isViewMovingLeft && m_camera.getCenter().x > int(Weight / 2))
        dx -= 50.0;
    if (m_isViewMovingRight && m_camera.getCenter().x < m_map.getMapSize().x * 128 - int(Weight / 2) - 50)
        dx += 50.0;

    if (m_isViewZoomingIn)
        zf = 1.1;
    if (m_isViewZoomingOut)
        zf = 0.9;

    m_camera.move(dx, dy);

    if (zf != 1.0)
        m_camera.zoom(zf);

    // if (!object->isAlive()) m_objects.remove(object);
}

void Game::renderObjects() {
    m_window.clear();

    m_window.setView(m_camera);
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

    if (key == sf::Keyboard::Escape) {
        m_bBPressed = false;
        m_BuildingChoosen = Buildings::nothing;
    }

    if (key == sf::Keyboard::Up)
        m_isViewMovingUp = isPressed;
    else if (key == sf::Keyboard::Down)
        m_isViewMovingDown = isPressed;
    else if (key == sf::Keyboard::Left)
        m_isViewMovingLeft = isPressed;
    else if (key == sf::Keyboard::Right)
        m_isViewMovingRight = isPressed;

    if (key == sf::Keyboard::Add)
        m_isViewZoomingOut = isPressed;
    else if (key == sf::Keyboard::Subtract)
        m_isViewZoomingIn = isPressed;

    if (key == sf::Keyboard::B && isPressed)
        m_bBPressed = true;

    if (isPressed && m_bBPressed) {
        if (key == sf::Keyboard::A)
            m_BuildingChoosen = Buildings::arsenal;
        else if (key == sf::Keyboard::C)
            m_BuildingChoosen = Buildings::cannon;
        else if (key == sf::Keyboard::F)
            m_BuildingChoosen = Buildings::factory;
        else if (key == sf::Keyboard::G)
            m_BuildingChoosen = Buildings::gen;
        else if (key == sf::Keyboard::L)
            m_BuildingChoosen = Buildings::lab;
        else if (key == sf::Keyboard::M)
            m_BuildingChoosen = Buildings::main;
        else if (key == sf::Keyboard::I)
            m_BuildingChoosen = Buildings::mine;
        else if (key == sf::Keyboard::N)
            m_BuildingChoosen = Buildings::nsilo;
        else if (key == sf::Keyboard::O)
            m_BuildingChoosen = Buildings::oil;
    }

    if (key == sf::Keyboard::Q)
        m_window.close();

    m_fileLogger->log("Game", "handlePlayerKeyboardEvent", "END");
}

void Game::handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed) {
    m_fileLogger->log("Game", "handlePlayerMouseEvent", "BEGIN");

    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    if (button == sf::Mouse::Right && isPressed) {
        m_consoleLogger->log("Game", "handlePlayerMouseEvent",
                             "Right pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }
    else if (button == sf::Mouse::Right && !isPressed) {
        m_consoleLogger->log("Game", "handlePlayerMouseEvent",
                             "Right released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }
    else if (button == sf::Mouse::Left && isPressed && m_bBPressed) {
        m_consoleLogger->log("Game", "handlePlayerMouseEvent",
                             "Left pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));

        if (m_BuildingChoosen != Buildings::nothing) {
            createBuilding(m_BuildingChoosen, worldPosition);
            m_bBPressed = false;
            m_BuildingChoosen = Buildings::nothing;
        }
    }
    else if (button == sf::Mouse::Left && !isPressed) {
        m_consoleLogger->log("Game", "handlePlayerMouseEvent",
                             "Left released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }

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