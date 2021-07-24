#include "TextureHolder.hpp"

namespace Textures {

    void TextureHolder::load(Textures::ID id, const std::string &fileName) {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());

        if (!texture->loadFromFile(fileName))
            throw std::runtime_error("Unable to load: " + fileName);

        auto inserted = m_TextureMap.insert(std::make_pair(id, std::move(texture)));
        assert(inserted.second);
    }

    sf::Texture &TextureHolder::get(Textures::ID id) {
        auto found = m_TextureMap.find(id);
        assert(found != m_TextureMap.end());

        return *found->second;
    }

    const sf::Texture &TextureHolder::get(Textures::ID id) const {
        auto found = m_TextureMap.find(id);
        assert(found != m_TextureMap.end());

        return *found->second;
    }

    void TextureHolder::init() {
        load(ID::Arsenal, "images/buildings/ArsenalBuilding.png");
        load(ID::Cannon, "images/buildings/CannonBuilding.png");
        load(ID::Factory, "images/buildings/FactoryBuilding.png");
        load(ID::Generator, "images/buildings/GeneratorBuilding.png");
        load(ID::Laboratory, "images/buildings/LaboratoryBuilding.png");
        load(ID::MainBase, "images/buildings/MainBaseBuilding.png");
        load(ID::Mine, "images/buildings/MineBuilding.png");
        load(ID::NuclearSilo, "images/buildings/NuclearSiloBuilding.png");
        load(ID::OilDerrick, "images/buildings/OilDerrickBuilding.png");

        load(ID::Car, "images/characters/CarCharacter.png");
        load(ID::NuclearRocket, "images/characters/NuclearRocketCharacter.png");
        load(ID::SpitFire, "images/characters/SpitFireCharacter.png");
        load(ID::Tank, "images/characters/TankCharacter.png");
        load(ID::Worker, "images/characters/WorkerCharacter.png");

        load(ID::Water, "images/tiles/water.png");
        load(ID::Meadow, "images/tiles/meadow.png");
        load(ID::Desert, "images/tiles/desert.png");
        load(ID::Mountain, "images/tiles/mountain.png");
        load(ID::OilSpot, "images/tiles/oilspot.png");
        load(ID::IronSpot, "images/tiles/ironspot.png");

        load(ID::Map, "images/maps/LostTemple.png");
        load(ID::Terrain, "images/tiles/terrain.png");

        load(ID::FireBlueCarShot, "images/shots/FireBlueCar.png");
        load(ID::FireRedTankShot, "images/shots/FireRedTank.png");
        load(ID::FireSpitFireShot, "images/shots/FireSpitFire.png");
        load(ID::FireWorkerShot, "images/shots/FireWorker.png");

        load(ID::SmallExplosion, "images/explosions/SmallExplosion.png");
        load(ID::MiddleExplosion, "images/explosions/MiddleExplosion.png");
        load(ID::BigExplosion, "images/explosions/BigExplosion.png");
    }
}