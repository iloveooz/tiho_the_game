#include "Map.hpp"

namespace World {

    Map::Map() {
        m_vMazeSize= sf::Vector2i(0, 0);
    }

    Map::~Map() {

    }

    void Map::loadLevel() {
        m_vMazeSize = sf::Vector2i(0, 0);
        m_vMazeData.clear();

        sf::Image levelData;

        if (!levelData.loadFromFile("images/maps/LostTemple.png"))
            throw std::runtime_error("Unable to load the map file");

        m_vMazeSize = sf::Vector2i(levelData.getSize());

        if (m_vMazeSize.x < 32 && m_vMazeSize.y < 32)
            throw  std::runtime_error("The loaded level is too small (min 32 cells large)");

        // loading maze data
        for (unsigned int y = 0; y < m_vMazeSize.y; y++) {
            for (unsigned int x = 0; x < m_vMazeSize.x; x++) {
                sf::Color cellData = levelData.getPixel(x, y);

                if (cellData == sf::Color::Yellow) {
                    m_vMazeData.push_back(Desert);
                }
                else if (cellData == sf::Color::White) {
                    m_vMazeData.push_back(IronSpot);
                }
                else if (cellData == sf::Color::Green) {
                    m_vMazeData.push_back(Meadow);
                }
                else if (cellData == sf::Color::Red) {
                    m_vMazeData.push_back(Mountain);
                }
                else if (cellData == sf::Color::Black) {
                    m_vMazeData.push_back(OilSpot);
                }
                else if (cellData == sf::Color::Blue) {
                    m_vMazeData.push_back(Water);
                }
                else if (cellData == sf::Color::Transparent) {
                    m_vMazeData.push_back(StartPoint);
                }
            }
        }

        m_renderTexture.create(128 * m_vMazeSize.x, 128 * m_vMazeSize.y);
        m_renderTexture.clear(sf::Color::Black);

        if (!m_DesertTexture.loadFromFile("images/tiles/desert.png"))
            throw std::runtime_error("Unable to load the desert tile file");

        if (!m_MeadowTexture.loadFromFile("images/tiles/meadow.png"))
            throw std::runtime_error("Unable to load the meadow tile file");

        if (!m_MountainTexture.loadFromFile("images/tiles/mountain.png"))
            throw std::runtime_error("Unable to load the mountain tile file");

        if (!m_WaterTexture.loadFromFile("images/tiles/water.png"))
            throw std::runtime_error("Unable to load the water tile file");

        if (!m_OilSpotTexture.loadFromFile("images/tiles/oilspot.png"))
            throw std::runtime_error("Unable to load the oilspot tile file");

        if (!m_IronSpotTexture.loadFromFile("images/tiles/ironspot.png"))
            throw std::runtime_error("Unable to load the ironspot tile file");

        if (!m_StartPointTexture.loadFromFile("images/tiles/empty.png"))
            throw std::runtime_error("Unable to load the empty tile file");

        sf::Sprite DesertSprite(m_DesertTexture);
        sf::Sprite MeadowSprite(m_MeadowTexture);
        sf::Sprite MountainSprite(m_MountainTexture);
        sf::Sprite WaterSprite(m_WaterTexture);
        sf::Sprite OilSpotSprite(m_OilSpotTexture);
        sf::Sprite IronSpotSprite(m_IronSpotTexture);
        sf::Sprite StartPointSprite(m_StartPointTexture);

        m_renderTexture.display();

        for (unsigned int i = 0; i < m_vMazeData.size(); i++) {
            sf::Vector2i position = indexToPosition(i);

            if (isCellDesert(position)) {
                DesertSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(DesertSprite);
            }

            if (isCellMeadow(position)) {
                MeadowSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(MeadowSprite);
            }

            if (isCellMountain(position)) {
                MountainSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(MountainSprite);
            }

            if (isCellWater(position)) {
                WaterSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(WaterSprite);
            }

            if (isCellIronSpot(position)) {
                IronSpotSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(IronSpotSprite);
            }

            if (isCellOilSpot(position)) {
                OilSpotSprite.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(OilSpotSprite);
            }

            if (isCellStartPoint(position)) {
                StartPointSprite.setPosition(32 * position.x, 32 * position.y);
                m_renderTexture.draw(StartPointSprite);
            }
        }
    }

    std::size_t Map::positionToIndex(sf::Vector2i position) const {
        return position.y * m_vMazeSize.x + position.x;
    }

    sf::Vector2i Map::indexToPosition(std::size_t index) const {
        sf::Vector2i position;

        position.x = index % m_vMazeSize.x;
        position.y = index / m_vMazeSize.x;

        return position;
    }

    bool Map::isCellEmpty(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == Empty;
    }

    bool Map::isCellWater(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == Water;
    }

    bool Map::isCellMeadow(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == Meadow;
    }

    bool Map::isCellDesert(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == Desert;
    }

    bool Map::isCellMountain(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == Mountain;
    }

    bool Map::isCellIronSpot(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == IronSpot;
    }

    bool Map::isCellOilSpot(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == OilSpot;
    }

    bool Map::isCellStartPoint(sf::Vector2i position) const {
        return m_vMazeData[positionToIndex(position)] == StartPoint;
    }
}