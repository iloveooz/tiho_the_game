#ifndef TIHO_TEXTUREHOLDER_HPP
#define TIHO_TEXTUREHOLDER_HPP

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

namespace Textures {
    enum ID {
        Empty,
        Arsenal,
        Cannon,
        Factory,
        Generator,
        Laboratory,
        MainBase,
        Mine,
        NuclearSilo,
        OilDerrick,
        Car,
        NuclearRocket,
        SpitFire,
        Tank,
        Worker,
        Water,
        Meadow,
        Desert,
        Mountain,
        OilSpot,
        IronSpot,
        StartPoint,
        Count
    };

    class TextureHolder : public IObject {
    public:
        void load(Textures::ID id, const std::string& fileName);

        sf::Texture& get(Textures::ID id);
        const sf::Texture& get(Textures::ID id) const;

    private:
        std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_TextureMap;
    };
}

#endif //TIHO_TEXTUREHOLDER_HPP
