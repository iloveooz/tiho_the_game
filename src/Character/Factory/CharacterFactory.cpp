#include "CharacterFactory.hpp"
#include "../Car.hpp"
#include "../NuclearRocket.hpp"
#include "../SpitFire.hpp"
#include "../Tank.hpp"
#include "../Worker.hpp"

namespace Factory {
    std::unique_ptr<Entity> CharacterFactory::createEntity(CharID charType) {
        switch (charType) {
            case car:
                return std::unique_ptr<Entity>(new Car);
            case nuke:
                return std::unique_ptr<Entity>(new NuclearRocket);
            case spit:
                return std::unique_ptr<Entity>(new SpitFire);
            case tank:
                return std::unique_ptr<Entity>(new Tank);
            case work:
                return std::unique_ptr<Entity>(new Worker);
            default:
                assert(false);
        }
    }
}