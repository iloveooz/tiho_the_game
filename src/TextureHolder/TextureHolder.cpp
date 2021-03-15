#include "TextureHolder.hpp"

namespace Textures {

    void TextureHolder::load(Textures::ID id, const std::string &fileName) {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());

        if (!texture->loadFromFile(fileName))
            throw std::runtime_error("Unable to load: " + fileName);

        m_TextureMap.insert(std::make_pair(id, std::move(texture)));
    }

    sf::Texture &TextureHolder::get(Textures::ID id) {
        auto found = m_TextureMap.find(id);
        return *found->second;
    }

    const sf::Texture &TextureHolder::get(Textures::ID id) const {
        auto found = m_TextureMap.find(id);
        return *found->second;
    }

    void TextureHolder::init() {
        load(Arsenal, "images/buildings/ArsenalBuilding.png");
        load(Cannon, "images/buildings/CannonBuilding.png");
        load(Factory, "images/buildings/FactoryBuilding.png");
        load(Generator, "images/buildings/GeneratorBuilding.png");
        load(Laboratory, "images/buildings/LaboratoryBuilding.png");
        load(MainBase, "images/buildings/MainBaseBuilding.png");
        load(Mine, "images/buildings/MineBuilding.png");
        load(NuclearSilo, "images/buildings/NuclearSiloBuilding.png");
        load(OilDerrick, "images/buildings/OilDerrickBuilding.png");

        load(Car, "images/characters/CarCharacter.png");
        load(NuclearRocket, "images/characters/NuclearRocketCharacter.png");
        load(SpitFire, "images/characters/SpitFireCharacter.png");
        load(Tank, "images/characters/TankCharacter.png");
        load(Worker, "images/characters/WorkerCharacter.png");

        load(Water, "images/tiles/water.png");
        load(Meadow, "images/tiles/meadow.png");
        load(Desert, "images/tiles/desert.png");
        load(Mountain, "images/tiles/mountain.png");
        load(OilSpot, "images/tiles/oilspot.png");
        load(IronSpot, "images/tiles/ironspot.png");

        load(Map, "images/maps/LostTemple.png");

        load(FireBlueCarShot, "images/shots/FireBlueCar.png");
        load(FireRedTankShot, "images/shots/FireRedTank.png");
        load(FireSpitFireShot, "images/shots/FireSpitFire.png");
        load(FireWorkerShot, "images/shots/FireWorker.png");

        load(SmallExplosion, "images/explosions/SmallExplosion.png");
        load(MiddleExplosion, "images/explosions/MiddleExplosion.png");
        load(BigExplosion, "images/explosions/BigExplosion.png");
    }
}