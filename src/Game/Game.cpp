#include "Game.hpp"

#include <memory>

#include "../Character/Factory/CharacterFactory.hpp"

Game::Game() :
        m_window(sf::VideoMode(Weight, Height), "Tycho Planet" /*, sf::Style::Fullscreen*/ ),
        m_consoleLogger(new ConsoleLogger()),
        m_fileLogger(new FileLogger("output.log")),
        m_cursor(sf::Sprite()) {

    m_fileLogger->log("Game", "Game", "BEGIN");

    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    m_camera.setSize(sf::Vector2f(Weight, Height));
    m_camera.setCenter(sf::Vector2f(Weight / 2, Height / 2));

    m_BuildingChoosen = Buildings::BuildID::nothing;

    m_textureHolder.init();

    m_sBackground.setTexture(m_textureHolder.get(Textures::ID::Terrain));

    m_animTank.setTexture(m_textureHolder.get(Textures::ID::Tank), 108, 108);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::tank, m_animTank));

    m_animCar.setTexture(m_textureHolder.get(Textures::ID::Car), 45, 45);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::car, m_animCar));

    m_animSpitFire.setTexture(m_textureHolder.get(Textures::ID::SpitFire), 48, 48);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::spit, m_animSpitFire));

    m_animNuke.setTexture(m_textureHolder.get(Textures::ID::NuclearRocket), 48, 48);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::nuke, m_animNuke));

    m_animWorker.setTexture(m_textureHolder.get(Textures::ID::Worker), 54, 54);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::work, m_animWorker));


    m_animArsenal.setTexture(m_textureHolder.get(Textures::ID::Arsenal), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::arsenal, m_animArsenal));

    m_animCannon.setTexture(m_textureHolder.get(Textures::ID::Cannon), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::cannon, m_animCannon));

    m_animFactory.setTexture(m_textureHolder.get(Textures::ID::Factory), 128, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::factory, m_animFactory));

    m_animGenerator.setTexture(m_textureHolder.get(Textures::ID::Generator), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::gen, m_animGenerator));

    m_animLab.setTexture(m_textureHolder.get(Textures::ID::Laboratory), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::lab, m_animLab));

    m_animMain.setTexture(m_textureHolder.get(Textures::ID::MainBase), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::main, m_animMain));

    m_animMine.setTexture(m_textureHolder.get(Textures::ID::Mine), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::mine, m_animMine));

    m_animNSilo.setTexture(m_textureHolder.get(Textures::ID::NuclearSilo), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::nsilo, m_animNSilo));

    m_animOil.setTexture(m_textureHolder.get(Textures::ID::OilDerrick), 64, 64);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::oil, m_animOil));


    m_animSmallExpl.setTexture(m_textureHolder.get(Textures::ID::SmallExplosion), Animations::ExplodeType::SmallExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::SmallExplode, m_animSmallExpl));

    m_animMiddleExpl.setTexture(m_textureHolder.get(Textures::ID::MiddleExplosion), Animations::ExplodeType::MiddleExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::MiddleExplode, m_animMiddleExpl));

    m_animBigExpl.setTexture(m_textureHolder.get(Textures::ID::BigExplosion), Animations::ExplodeType::BigExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::BigExplode, m_animBigExpl));

    m_fileLogger->log("Game", "Game", "END");
}

Game::~Game() {
}

void Game::run() {
    m_fileLogger->log("Game", "run", "BEGIN");

    prepareGame();

    while (m_window.isOpen()) {
        checkMousePosition();
        showTemplateOfBuilding();
        processEvents();
        updateViewOfMap();
        renderObjects();
    }

    m_fileLogger->log("Game", "run", "END");
}

void Game::prepareGame() {
    fillGameStates();
    changeGameState(States::TypeState::Playing);

    createMap();
}

void Game::createCharacter(Factory::CharID id, sf::Vector2f position) {
    m_fileLogger->log("Game", "createCharacter", "BEGIN");

    Factory::CharacterFactory factory;

    std::unique_ptr<Entity> character = factory.createEntity(id);
    placeCharacter(id, position);
    character->settings(m_CharAnimap.find(id)->second, position.x, position.y, 0);
    m_characters.push_back(std::move(character));

    m_fileLogger->log("Game", "createCharacter", "END");
}

void Game::placeCharacter(Factory::CharID id, sf::Vector2f& position) {
    int inX = int(position.x) / 128;
    int inY = int(position.y) / 128;

    if (id == Factory::CharID::work) {
        position.x = float(inX) * 128 - 86;
        position.y = float(inY) * 128 + 170;
    }
}

void Game::createBuilding(Buildings::BuildID id, sf::Vector2f position) {
    m_fileLogger->log("Game", "createBuilding", "BEGIN");

    setBuildingToGrid(id, position);

    std::unique_ptr<Buildings::Building> building = Buildings::Building::createBuilding(id);
    building->settings(m_BuildAnimap.find(id)->second, position.x, position.y, 0);
    m_buildings.push_back(std::move(building));

    m_cursor.setVisible(false);

    m_fileLogger->log("Game", "createBuilding", "END");
}

void Game::destroyBuilding() {
    m_fileLogger->log("Game", "destroyBuilding", "BEGIN");

    for (unsigned int i = 0; i < m_buildings.size(); i++) {
        if (m_buildings[i]->isSelected()) {

            sf::Vector2f position = m_buildings[i]->getSprite().getPosition();

            m_buildings.erase(m_buildings.begin() + i--);
            m_cursor.setVisible(false);
            m_consoleLogger->log("Game", "destroyBuilding", "DESTROY!");
            explodeBuilding(position);
        }
    }

    m_fileLogger->log("Game", "destroyBuilding", "END");
}

void Game::explodeBuilding(sf::Vector2f position) {
    m_fileLogger->log("Game", "explodeBuilding", "BEGIN");

    std::unique_ptr<Entity> explode = std::make_unique<Entity>();
    explode->settings(m_ExplodeAnimap.find(Animations::ExplodeType::BigExplode)->second, position.x, position.y, 0);
    explode->setName("explosion");
    m_characters.push_back(std::move(explode));

    m_fileLogger->log("Game", "explodeBuilding", "END");
}

void Game::selectBuilding() {
    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    int countBuilding = 0;

    for (auto& building : m_buildings) {
        if (building->getSprite().getGlobalBounds().contains(worldPosition.x, worldPosition.y)) {
            m_consoleLogger->log("Game", "selectBuilding", building->getName() + " selected!");
            building->setSelected(true);
            countBuilding++;

            m_cursor.setSprite(building->getSprite());
            m_cursor.setVisible(true);
        } else {
            building->setSelected(false);
            m_consoleLogger->log("Game", "selectBuilding", building->getName() + " deselected!");
        }
    }

    if (countBuilding == 0)
        m_cursor.setVisible(false);
}

void Game::setBuildingToGrid(Buildings::BuildID id, sf::Vector2f &position) {
    int inX = int(position.x) / 128;
    int inY = int(position.y) / 128;

    switch (id) {
        case Buildings::BuildID::main:
            position.x = float(inX) * 128;
            position.y = float(inY) * 128;
            break;
        case Buildings::BuildID::factory:
            position.x = float(inX) * 128;
            position.y = float(inY) * 128 + 64;
            break;
        default:
            position.x = float(inX) * 128 + 64;
            position.y = float(inY) * 128 + 64;
    }
}

void Game::showTemplateOfBuilding() {
    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    if (m_BuildingChoosen != Buildings::BuildID::nothing) {
        m_fakeBuilding = m_BuildAnimap.find(m_BuildingChoosen)->second.getSprite();
        setBuildingToGrid(m_BuildingChoosen, worldPosition);
        m_fakeBuilding.setColor(sf::Color(0, 0, 0, 96));
        m_fakeBuilding.move(worldPosition);
    }
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

    // if (!object->isAlive()) m_characters.remove(object);
}

void Game::renderObjects() {
    m_window.clear();

    m_window.setView(m_camera);
    m_window.draw(m_map);

    // отображение юнитов
    for (auto const &object : m_characters) {
        if (object->getName() == "explosion") {
            // m_consoleLogger->log("Game", "renderObjects", "Explosion!");
            (reinterpret_cast<Animations::ExplosionAnimation &>(object->getAnimation())).update();
            // m_consoleLogger->log("Game", "renderObjects", "Doned!");
        }
        object->draw(m_window);
    }

    // отображение зданий
    for (auto const &object : m_buildings)
        object->draw(m_window);

    // отображение курсора
    m_cursor.draw(m_window);

    if (m_BuildingChoosen != Buildings::BuildID::nothing) {
        m_window.draw(m_fakeBuilding);
    }

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
            case sf::Event::MouseWheelScrolled:
                handlePlayerMouseWheelEvent(event);
        }
    }
}

void Game::handlePlayerKeyboardEvent(sf::Keyboard::Key key, bool isPressed) {
    m_fileLogger->log("Game", "handlePlayerKeyboardEvent", "BEGIN");

    if (key == sf::Keyboard::Escape) {
        m_bBPressed = false;
        m_bCPressed = false;

        m_bDPressed = false;
        m_bDDPressed = false;

        m_BuildingChoosen = Buildings::BuildID::nothing;
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

    if (m_bDDPressed) {
        destroyBuilding();
        m_bDPressed = false;
        m_bDDPressed = false;
    }

    if (key == sf::Keyboard::C && isPressed)
        m_bCPressed = true;

    if (key == sf::Keyboard::D && isPressed && m_bDPressed)
        m_bDDPressed = true;

    if (key == sf::Keyboard::D && isPressed)
        m_bDPressed = true;

    if (isPressed && m_bBPressed) {
        if (key == sf::Keyboard::A)
            m_BuildingChoosen = Buildings::BuildID::arsenal;
        else if (key == sf::Keyboard::C)
            m_BuildingChoosen = Buildings::BuildID::cannon;
        else if (key == sf::Keyboard::F)
            m_BuildingChoosen = Buildings::BuildID::factory;
        else if (key == sf::Keyboard::G)
            m_BuildingChoosen = Buildings::BuildID::gen;
        else if (key == sf::Keyboard::L)
            m_BuildingChoosen = Buildings::BuildID::lab;
        else if (key == sf::Keyboard::M)
            m_BuildingChoosen = Buildings::BuildID::main;
        else if (key == sf::Keyboard::I)
            m_BuildingChoosen = Buildings::BuildID::mine;
        else if (key == sf::Keyboard::N)
            m_BuildingChoosen = Buildings::BuildID::nsilo;
        else if (key == sf::Keyboard::O)
            m_BuildingChoosen = Buildings::BuildID::oil;
    }

    if (m_bCPressed) {
        for (auto& building : m_buildings) {
            if (building->getName() == "main" && building->isSelected())
                createCharacter(Factory::CharID::work, building->getPosition());
        }
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
        m_consoleLogger->log(__PRETTY_FUNCTION__, "",
                             "Right pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }
    else if (button == sf::Mouse::Right && !isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "",
                             "Right released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }
    else if (button == sf::Mouse::Left && isPressed && m_bBPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "",
                             "Left pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));

        if (m_BuildingChoosen != Buildings::BuildID::nothing) {
            createBuilding(m_BuildingChoosen, worldPosition);
            m_bBPressed = false;
            m_BuildingChoosen = Buildings::BuildID::nothing;
        }
    }
    else if (button == sf::Mouse::Left && isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "",
                             "Left pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
        selectBuilding();
    }
    else if (button == sf::Mouse::Left && !isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "",
                             "Left released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " +
                             std::to_string(windowPosition.y));
    }

    m_fileLogger->log("Game", "handlePlayerMouseEvent", "END");
}

void Game::handlePlayerMouseWheelEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta >= 1) {
            m_camera.zoom(1 - 0.25f);
        }
        else {
            m_camera.zoom(1 + 0.25f);
        }
    }
}

void Game::changeGameState(States::TypeState gameState) {
    m_fileLogger->log("Game", "changeGameState", "BEGIN");

    m_pCurrentState = std::move(m_gameStates[static_cast<int>(gameState)]);

    m_fileLogger->log("Game", "changeGameState", "END");
}

void Game::fillGameStates() {
    m_fileLogger->log("Game", "fillGameStates", "BEGIN");

    m_gameStates[static_cast<int>(States::TypeState::Menu)] = std::make_unique<States::MenuState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Playing)] = std::make_unique<States::PlayingState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Won)] = std::make_unique<States::WonState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Lost)] = std::make_unique<States::LostState>(shared_from_this());

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

World::Map& Game::getMap() {
    return m_map;
}
