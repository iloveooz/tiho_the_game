#ifndef TIHO_MAP_HPP
#define TIHO_MAP_HPP

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"
#include "../TextureHolder/TextureHolder.hpp"

namespace World {

    enum class CellType {
        Empty,
        Water,
        Meadow,
        Desert,
        Mountain,
        OilSpot,
        IronSpot,
        StartPoint,
        Count
    };

class Map : public IObject, public sf::Drawable {
    public:
        Map();

        virtual ~Map();

        bool isCellEmpty(sf::Vector2i position) const;
        bool isCellWater(sf::Vector2i position) const;
        bool isCellMeadow(sf::Vector2i position) const;
        bool isCellDesert(sf::Vector2i position) const;
        bool isCellMountain(sf::Vector2i position) const;

        bool isCellIronSpot(sf::Vector2i position) const;
        bool isCellOilSpot(sf::Vector2i position) const;

        bool isCellStartPoint(sf::Vector2i position) const;

        // helpers (inline = faster)
        inline std::size_t positionToIndex(sf::Vector2i position) const;
        inline sf::Vector2i indexToPosition(std::size_t index) const;

        void loadLevel(const Textures::TextureHolder& textureHolder);

        sf::Vector2i getMapSize() const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2i m_vMazeSize;
        std::vector<CellType> m_vMazeData;

        sf::Sprite m_sDesert;
        sf::Sprite m_sMeadow;
        sf::Sprite m_sMountain;
        sf::Sprite m_sWater;
        sf::Sprite m_sOilSpot;
        sf::Sprite m_sIronSpot;
        sf::Sprite m_sStartPoint;

        sf::RenderTexture m_renderTexture;
    };
}
#endif //TIHO_MAP_HPP
