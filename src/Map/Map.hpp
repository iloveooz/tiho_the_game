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
        Mountain
    };

    class Map : public IObject {
    public:
        Map();

        Map(const sf::Vector2i &mMazeSize);

        virtual ~Map();

        bool isCellEmpty() const;
        bool isCellWater() const;
        bool isCellMeadow() const;
        bool isCellDesert() const;
        bool isCellMountain() const;

    private:
        sf::Vector2i m_vMazeSize;
        std::vector<CellType> m_vMazeData;

    };
}
#endif //TIHO_MAP_HPP
