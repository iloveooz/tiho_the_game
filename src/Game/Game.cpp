#include "Game.hpp"

#include <memory>

#include "../Character/Factory/CharacterFactory.hpp"
#include "../Explosion/Explosion.hpp"

Game::Game() :
        m_window(sf::VideoMode(Weight, Height), "Tycho Planet" /*, sf::Style::Fullscreen*/ ),
        m_consoleLogger(new ConsoleLogger()),
        m_fileLogger(new FileLogger("output.log")) {

    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);

    m_amountTanks = 5;

    m_camera.setSize(sf::Vector2f(Weight, Height));
    m_camera.setCenter(sf::Vector2f(Weight / 2, Height / 2));

    m_BuildingChoosen = Buildings::BuildID::nothing;

    m_isViewZoomingIn = false;
    m_isViewZoomingOut = false;

    m_textureHolder.init();

    m_animTank.setTexture(m_textureHolder.get(Textures::ID::Tank), 128, 128);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::tank, m_animTank));

    m_animCar.setTexture(m_textureHolder.get(Textures::ID::Car), 128, 128);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::car, m_animCar));

    m_animSpitFire.setTexture(m_textureHolder.get(Textures::ID::SpitFire), 128, 128);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::spit, m_animSpitFire));

    m_animNuke.setTexture(m_textureHolder.get(Textures::ID::NuclearRocket), 128, 128);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::nuke, m_animNuke));

    m_animWorker.setTexture(m_textureHolder.get(Textures::ID::Worker), 128, 128);
    m_CharAnimap.insert(std::make_pair(Factory::CharID::work, m_animWorker));


    m_animArsenal.setTexture(m_textureHolder.get(Textures::ID::Arsenal), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::arsenal, m_animArsenal));

    m_animCannon.setTexture(m_textureHolder.get(Textures::ID::Cannon), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::cannon, m_animCannon));

    m_animFactory.setTexture(m_textureHolder.get(Textures::ID::Factory), 256, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::factory, m_animFactory));

    m_animGenerator.setTexture(m_textureHolder.get(Textures::ID::Generator), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::gen, m_animGenerator));

    m_animLab.setTexture(m_textureHolder.get(Textures::ID::Laboratory), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::lab, m_animLab));

    m_animMain.setTexture(m_textureHolder.get(Textures::ID::MainBase), 256, 256);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::main, m_animMain));

    m_animMine.setTexture(m_textureHolder.get(Textures::ID::Mine), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::mine, m_animMine));

    m_animNSilo.setTexture(m_textureHolder.get(Textures::ID::NuclearSilo), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::nsilo, m_animNSilo));

    m_animOil.setTexture(m_textureHolder.get(Textures::ID::OilDerrick), 128, 128);
    m_BuildAnimap.insert(std::make_pair(Buildings::BuildID::oil, m_animOil));


    m_animSmallExpl.setTexture(m_textureHolder.get(Textures::ID::SmallExplosion), Animations::ExplodeType::SmallExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::SmallExplode, m_animSmallExpl));

    m_animMiddleExpl.setTexture(m_textureHolder.get(Textures::ID::MiddleExplosion), Animations::ExplodeType::MiddleExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::MiddleExplode, m_animMiddleExpl));

    m_animBigExpl.setTexture(m_textureHolder.get(Textures::ID::BigExplosion), Animations::ExplodeType::BigExplode);
    m_ExplodeAnimap.insert(std::make_pair(Animations::ExplodeType::BigExplode, m_animBigExpl));

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

Game::~Game() {
}

void Game::run() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    prepareGame();

    while (m_window.isOpen()) {
        checkMousePosition();
        showTemplateOfBuilding();
        processEvents();
        updateViewOfMap();
        renderObjects();
        checkAliveEntities();
    }

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::prepareGame() {
    fillGameStates();
    changeGameState(States::TypeState::Playing);

    createMap();
}

void Game::createCharacter(Factory::CharID id, sf::Vector2f position) {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    Factory::CharacterFactory factory;

    std::unique_ptr<Entity> character = factory.createEntity(id);
    placeCharacter(id, position);
    character->settings(m_CharAnimap.find(id)->second, position.x, position.y, 0);
    m_characters.push_back(std::move(character));

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::placeCharacter(Factory::CharID id, sf::Vector2f& position) {
    int inX = int(position.x) / 128;
    int inY = int(position.y) / 128;

    if (id == Factory::CharID::nuke) {
        position.x = float(inX) * 128 + 64;
        position.y = float(inY) * 128 + 64;
    } else {
        position.x = float(inX - 1) * 128 + 64;
        position.y = float(inY + 1) * 128 + 64;
    }
}

void Game::destroyCharacter() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    for (auto& character : m_characters) {
        if (character->isSelected()) {
            sf::Vector2f position = character->getSprite().getPosition();
            character->getCursor().setVisible(false);
            character->setDead();
            m_consoleLogger->log(__PRETTY_FUNCTION__, "DESTROY!");
            explodeCharacter(position);
        }
    }

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::explodeCharacter(sf::Vector2f position) {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    std::unique_ptr<Entity> explode = std::make_unique<Explosion>();
    explode->settings(m_ExplodeAnimap.find(Animations::ExplodeType::MiddleExplode)->second, position.x, position.y, 0);
    explode->setName("explosion");
    m_characters.push_back(std::move(explode));

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::createBuilding(Buildings::BuildID id, sf::Vector2f position) {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    setBuildingToGrid(id, position);

    std::unique_ptr<Buildings::Building> building = Buildings::Building::createBuilding(id);
    building->settings(m_BuildAnimap.find(id)->second, position.x, position.y, 0);
    building->getCursor().setVisible(false);
    m_buildings.push_back(std::move(building));

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::destroyBuilding() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    for (unsigned int i = 0; i < m_buildings.size(); i++) {
        if (m_buildings[i]->isSelected()) {

            sf::Vector2f position = m_buildings[i]->getSprite().getPosition();
            m_buildings[i]->getCursor().setVisible(false);
            m_buildings.erase(m_buildings.begin() + i--);

            m_consoleLogger->log(__PRETTY_FUNCTION__, "DESTROY!");
            explodeBuilding(position);
        }
    }

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::explodeBuilding(sf::Vector2f& position) {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    std::unique_ptr<Entity> explode = std::make_unique<Explosion>();
    explode->settings(m_ExplodeAnimap.find(Animations::ExplodeType::BigExplode)->second, position.x, position.y, 0);
    explode->setName("explosion");
    m_characters.push_back(std::move(explode));

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::selectObjectOnMap() {
    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    int countBuilding = 0;

    for (auto& building : m_buildings) {
        if (building->getSprite().getGlobalBounds().contains(worldPosition.x, worldPosition.y)) {
            m_consoleLogger->log(__PRETTY_FUNCTION__, building->getName() + " selected!");
            building->setSelected(true);
            countBuilding++;

            building->getCursor().setSprite(building->getSprite());
            building->getCursor().setVisible(true);
        } else {
            building->setSelected(false);
            building->getCursor().setVisible(false);
            m_consoleLogger->log(__PRETTY_FUNCTION__, building->getName() + " deselected!");
        }
    }

    for (auto& character : m_characters) {
        if (character->getSprite().getGlobalBounds().contains(worldPosition.x, worldPosition.y)) {
            m_consoleLogger->log(__PRETTY_FUNCTION__, character->getName() + " selected!");
            character->setSelected(true);
            countBuilding++;

            character->getCursor().setSprite(character->getSprite());
            character->getCursor().setVisible(true);
        } else {
            character->setSelected(false);
            character->getCursor().setVisible(false);
            m_consoleLogger->log(__PRETTY_FUNCTION__, character->getName() + " deselected!");
        }
    }

    if (countBuilding == 0) {}
        // m_cursor.setVisible(false);
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
    // m_consoleLogger->log(__PRETTY_FUNCTION__, "x = " + std::to_string(mousePosition.x) + ", y = " + std::to_string(mousePosition.y));

    m_isViewMovingLeft = (mousePosition.x < 3);
    m_isViewMovingRight = (mousePosition.x > m_window.getSize().x - 3);
    m_isViewMovingUp = (mousePosition.y < 3);
    m_isViewMovingDown = (mousePosition.y > m_window.getSize().y - 3);
}

void Game::centerViewOfMap() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    for (auto& building : m_buildings) {
        if (building->isSelected())
            m_camera.setCenter(building->getPosition());
    }

    for (auto& character : m_characters) {
        if (character->isSelected())
            m_camera.setCenter(character->getPosition());
    }

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
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
}

void Game::renderObjects() {
    m_window.clear();

    m_window.setView(m_camera);
    m_window.draw(m_map);

    // отображение юнитов
    for (auto const &object : m_characters) {
        if (object->getName() == "explosion" && object->isAlive()) {
            object->getAnimation().update();

            if (object->getAnimation().isEnd()) {
                object->setDead();
            }
        }

        if (object->isMoving()) {
            // TODO - сделать по-человечески, выглядит стрёмно
            object->getCursor().setSprite(object->getSprite());
            object->getCursor().update();
            object->update();
        }

        // отображение курсора
        if (object->getCursor().getVisible())
            object->getCursor().update();

        object->getCursor().draw(m_window);

        object->draw(m_window);
    }

    // отображение зданий
    for (auto const &object : m_buildings) {
        object->draw(m_window);

        // отображение курсора
        if (object->getCursor().getVisible())
            object->getCursor().update();

        object->getCursor().draw(m_window);
    }

    if (m_BuildingChoosen != Buildings::BuildID::nothing) {
        m_window.draw(m_fakeBuilding);
    }

    m_window.display();
}

void Game::checkAliveEntities() {
    for (unsigned int i = 0; i < m_characters.size(); i++) {
        if (!m_characters[i]->isAlive()) {
            m_characters.erase(m_characters.begin() + i--);
        }
    }
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
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    sf::Vector2f mainBasePosition;

    if (key == sf::Keyboard::Escape) {
        m_bBPressed = false;

        m_ePressedProperty = eKeyPressed::empty;

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

    if (key == sf::Keyboard::Space && isPressed)
        centerViewOfMap();

    if (key == sf::Keyboard::B && isPressed)
        m_bBPressed = true;

    if (m_bDDPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Destroy command");
        destroyBuilding();
        destroyCharacter();
        m_bDPressed = false;
        m_bDDPressed = false;
    }

    if (key == sf::Keyboard::W && isPressed)
        m_ePressedProperty = eKeyPressed::WPressed;

    if (key == sf::Keyboard::C && isPressed)
        m_ePressedProperty = eKeyPressed::CPressed;

    if (key == sf::Keyboard::T && isPressed)
        m_ePressedProperty = eKeyPressed::TPressed;

    if (key == sf::Keyboard::S && isPressed)
        m_ePressedProperty = eKeyPressed::SPressed;

    if (key == sf::Keyboard::R && isPressed)
        m_ePressedProperty = eKeyPressed::RPressed;

    if (key == sf::Keyboard::P && isPressed)
        m_ePressedProperty = eKeyPressed::PPressed;

    if (key == sf::Keyboard::H && isPressed)
        m_ePressedProperty = eKeyPressed::HPressed;


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

    if (m_ePressedProperty != eKeyPressed::empty && isPressed) {
        for (auto& building : m_buildings) {
            if (building->getName() == "main")
                mainBasePosition = building->getPosition();

            if (building->getName() == "main" && building->isSelected() && m_ePressedProperty == eKeyPressed::WPressed) {
                createCharacter(Factory::CharID::work, mainBasePosition);
            }

            if (building->getName() == "factory" && building->isSelected()) {
                if (m_ePressedProperty == eKeyPressed::CPressed)
                    createCharacter(Factory::CharID::car, building->getPosition());
                if (m_ePressedProperty == eKeyPressed::TPressed)
                    createCharacter(Factory::CharID::tank, building->getPosition());
                if (m_ePressedProperty == eKeyPressed::SPressed)
                    createCharacter(Factory::CharID::spit, building->getPosition());
            }

            if (building->getName() == "nsilo" && building->isSelected()) {
                if (m_ePressedProperty == eKeyPressed::RPressed)
                    createCharacter(Factory::CharID::nuke, building->getPosition());
            }
        }

        for (auto& character : m_characters) {
            if (character->isSelected() && character->getName() != "nuclearrocket" && m_ePressedProperty == eKeyPressed::SPressed) {
                m_consoleLogger->log(__PRETTY_FUNCTION__, "Stop command");
                m_comManager.handleCommand(Commands::UnitAction::Stop, character, worldPosition);
            }

            if (character->isSelected() && character->getName() != "nuclearrocket" && m_ePressedProperty == eKeyPressed::HPressed) {
                m_consoleLogger->log(__PRETTY_FUNCTION__, "Hold command");
                m_comManager.handleCommand(Commands::UnitAction::Hold, character, mainBasePosition);
            }
        }

        if (m_ePressedProperty != eKeyPressed::PPressed)
            m_ePressedProperty = eKeyPressed::empty;
    }

    if (key == sf::Keyboard::Q)
        m_window.close();

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::handlePlayerMouseEvent(sf::Mouse::Button button, bool isPressed) {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    sf::Vector2i windowPosition = sf::Mouse::getPosition(m_window);
    sf::Vector2f worldPosition = m_window.mapPixelToCoords(windowPosition);

    if (button == sf::Mouse::Right && isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Right pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " + std::to_string(windowPosition.y));

        for (auto& character : m_characters) {
            if (character->isSelected() && m_ePressedProperty != eKeyPressed::PPressed) {
                m_consoleLogger->log(__PRETTY_FUNCTION__, "Go command");
                m_comManager.handleCommand(Commands::UnitAction::Go, character, worldPosition);
            }

            if (character->isSelected() && m_ePressedProperty == eKeyPressed::PPressed) {
                m_consoleLogger->log(__PRETTY_FUNCTION__, "Patrol command");
                m_comManager.handleCommand(Commands::UnitAction::Patrol, character, worldPosition);
                m_ePressedProperty = eKeyPressed::empty;
            }
        }
    }

    else if (button == sf::Mouse::Right && !isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Right released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " + std::to_string(windowPosition.y));
    }

    else if (button == sf::Mouse::Left && isPressed && m_bBPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Left pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " + std::to_string(windowPosition.y));

        if (m_BuildingChoosen != Buildings::BuildID::nothing) {
            createBuilding(m_BuildingChoosen, worldPosition);
            m_bBPressed = false;
            m_BuildingChoosen = Buildings::BuildID::nothing;
        }
    }

    else if (button == sf::Mouse::Left && isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Left pressed! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " + std::to_string(windowPosition.y));
        selectObjectOnMap();
    }

    else if (button == sf::Mouse::Left && !isPressed) {
        m_consoleLogger->log(__PRETTY_FUNCTION__, "Left released! Coordinates: x = " + std::to_string(windowPosition.x) + ", y = " + std::to_string(windowPosition.y));
    }

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
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
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    m_pCurrentState = std::move(m_gameStates[static_cast<int>(gameState)]);

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::fillGameStates() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    m_gameStates[static_cast<int>(States::TypeState::Menu)] = std::make_unique<States::MenuState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Playing)] = std::make_unique<States::PlayingState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Won)] = std::make_unique<States::WonState>(shared_from_this());
    m_gameStates[static_cast<int>(States::TypeState::Lost)] = std::make_unique<States::LostState>(shared_from_this());

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
}

void Game::createMap() {
    m_fileLogger->log(__PRETTY_FUNCTION__, "BEGIN");

    m_map.loadLevel(m_textureHolder);

    m_fileLogger->log(__PRETTY_FUNCTION__, "END");
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
