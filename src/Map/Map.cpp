#include "Map.hpp"

namespace World {

    Map::Map() {
        m_vMazeSize = sf::Vector2i(0, 0);
    }

    Map::~Map() {

    }

    void Map::loadLevel(const Textures::TextureHolder& textureHolder) {
        m_vMazeSize = sf::Vector2i(0, 0);
        m_vMazeData.clear();

        sf::Image levelData = textureHolder.get(Textures::Map).copyToImage();;

        m_vMazeSize = sf::Vector2i(levelData.getSize());

        if (m_vMazeSize.x < 32 && m_vMazeSize.y < 32)
            throw std::runtime_error("The loaded level is too small (min 32 cells large)");

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

        m_sDesert.setTexture(textureHolder.get(Textures::Desert));
        m_sMeadow.setTexture(textureHolder.get(Textures::Meadow));
        m_sMountain.setTexture(textureHolder.get(Textures::Mountain));
        m_sWater.setTexture(textureHolder.get(Textures::Water));
        m_sOilSpot.setTexture(textureHolder.get(Textures::OilSpot));
        m_sIronSpot.setTexture(textureHolder.get(Textures::IronSpot));

        m_renderTexture.display();

        for (unsigned int i = 0; i < m_vMazeData.size(); i++) {
            sf::Vector2i position = indexToPosition(i);

            if (isCellDesert(position)) {
                m_sDesert.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sDesert);
            }

            if (isCellMeadow(position)) {
                m_sMeadow.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sMeadow);
            }

            if (isCellMountain(position)) {
                m_sMountain.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sMountain);
            }

            if (isCellWater(position)) {
                m_sWater.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sWater);
            }

            if (isCellIronSpot(position)) {
                m_sOilSpot.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sOilSpot);
            }

            if (isCellOilSpot(position)) {
                m_sIronSpot.setPosition(128 * position.x, 128 * position.y);
                m_renderTexture.draw(m_sIronSpot);
            }

            if (isCellStartPoint(position)) {
                m_sStartPoint.setPosition(32 * position.x, 32 * position.y);
                m_renderTexture.draw(m_sStartPoint);
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

    void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(sf::Sprite(m_renderTexture.getTexture()), states);
    }

    sf::Vector2i Map::getMapSize() const {
        return m_vMazeSize;
    }
}