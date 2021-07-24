#include "CharacterFactory.hpp"
#include "../Car.hpp"
#include "../NuclearRocket.hpp"
#include "../SpitFire.hpp"
#include "../Tank.hpp"
#include "../Worker.hpp"

namespace Factory {
    std::unique_ptr<Entity> CharacterFactory::createEntity(CharID charType) {
        switch (charType) {
            case CharID::car:
                return std::unique_ptr<Entity>(new Car);
            case CharID::nuke:
                return std::unique_ptr<Entity>(new NuclearRocket);
            case CharID::spit:
                return std::unique_ptr<Entity>(new SpitFire);
            case CharID::tank:
                return std::unique_ptr<Entity>(new Tank);
            case CharID::work:
                return std::unique_ptr<Entity>(new Worker);
            default:
                assert(false);
        }
    }
}