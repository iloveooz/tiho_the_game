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
        StartPoint
    };

    class Map : public IObject {
    public:
        Map();

        Map(const sf::Vector2i &mMazeSize);

        virtual ~Map();

        bool isCellEmpty(sf::Vector2i position) const;
        bool isCellWater(sf::Vector2i position) const;
        bool isCellMeadow(sf::Vector2i position) const;
        bool isCellDesert(sf::Vector2i position) const;
        bool isCellMountain(sf::Vector2i position) const;

        bool isCellIronSpot(sf::Vector2i position) const;
        bool isCellOilSpot(sf::Vector2i position) const;

        bool isCellStartPoint(sf::Vector2i position) const;

        void loadLevel();

    private:
        sf::Vector2i m_vMazeSize;
        std::vector<CellType> m_vMazeData;

    };
}
#endif //TIHO_MAP_HPP
