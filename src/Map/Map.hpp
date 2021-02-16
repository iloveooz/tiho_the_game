#ifndef TIHO_MAP_HPP
#define TIHO_MAP_HPP

#include <SFML/Graphics.hpp>
#include "../IObject/IObject.hpp"

namespace World {

    enum CellType {
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

        void loadLevel();

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Vector2i m_vMazeSize;
        std::vector<CellType> m_vMazeData;

        sf::RenderTexture m_renderTexture;

        sf::Texture m_DesertTexture;
        sf::Texture m_MeadowTexture;
        sf::Texture m_MountainTexture;
        sf::Texture m_WaterTexture;

        sf::Texture m_OilSpotTexture;
        sf::Texture m_IronSpotTexture;

        sf::Texture m_StartPointTexture;

    };
}
#endif //TIHO_MAP_HPP
