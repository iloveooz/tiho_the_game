#ifndef TIHO_MAP_HPP
#define TIHO_MAP_HPP

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
        virtual ~Map();

        bool isCellEmpty() const;
        bool isCellWater() const;
        bool isCellMeadow() const;
        bool isCellDesert() const;
        bool isCellMountain() const;

    };
}
#endif //TIHO_MAP_HPP
