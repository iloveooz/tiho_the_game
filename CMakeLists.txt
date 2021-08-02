cmake_minimum_required(VERSION 3.10)
project(tiho)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

set(SOURCE_FILES
        src/main.cpp

        src/Character/Car.cpp
        src/Character/Car.hpp

        src/Character/Tank.cpp
        src/Character/Tank.hpp

        src/Character/Worker.cpp
        src/Character/Worker.hpp

        src/Character/Entity.cpp
        src/Character/Entity.hpp

        src/IObject/IObject.hpp
        src/IObject/IObject.cpp

        src/Game/Game.cpp
        src/Game/Game.hpp

        src/Map/Map.cpp
        src/Map/Map.hpp

        src/Game/GameState.cpp
        src/Game/GameState.hpp

        src/Character/Factory/CharacterFactory.hpp
        src/Character/Factory/CharacterFactory.cpp

        src/Resource/Iron.cpp
        src/Resource/Iron.hpp

        src/Resource/Oil.cpp
        src/Resource/Oil.hpp

        src/Resource/Energy.cpp
        src/Resource/Energy.hpp

        src/Building/MainBaseBuilding.cpp
        src/Building/MainBaseBuilding.hpp

        src/Building/GeneratorBuilding.cpp
        src/Building/GeneratorBuilding.hpp

        src/Building/MineBuilding.cpp
        src/Building/MineBuilding.hpp

        src/Building/Building.cpp
        src/Building/Building.hpp

        src/Building/OilDerrickBuilding.cpp
        src/Building/OilDerrickBuilding.hpp

        src/Building/FactoryBuilding.cpp
        src/Building/FactoryBuilding.hpp

        src/Building/ArsenalBuilding.cpp
        src/Building/ArsenalBuilding.hpp

        src/Building/CannonBuilding.cpp
        src/Building/CannonBuilding.hpp

        src/Building/LaboratoryBuilding.cpp
        src/Building/LaboratoryBuilding.hpp

        src/Building/NuclearSiloBuilding.cpp
        src/Building/NuclearSiloBuilding.hpp

        src/Game/MenuState.cpp
        src/Game/MenuState.hpp

        src/Game/PlayingState.cpp
        src/Game/PlayingState.hpp

        src/Game/WonState.cpp
        src/Game/WonState.hpp

        src/Game/LostState.cpp
        src/Game/LostState.hpp

        src/Character/SpitFire.cpp
        src/Character/SpitFire.hpp

        src/Character/NuclearRocket.cpp
        src/Character/NuclearRocket.hpp

        src/Character/Commands/UnitCommand.cpp
        src/Character/Commands/UnitCommand.hpp

        src/Character/Commands/UnitCommandsManager.cxx
        src/Character/Commands/UnitCommandsManager.hxx

        src/Character/Commands/GoCommand.cpp
        src/Character/Commands/GoCommand.hpp

        src/Character/Commands/StopCommand.cpp
        src/Character/Commands/StopCommand.hpp

        src/Character/Commands/AttackCommand.cpp
        src/Character/Commands/AttackCommand.hpp

        src/Character/Commands/RepairCommand.cpp
        src/Character/Commands/RepairCommand.hpp

        src/Character/Commands/HoldPositionCommand.cpp
        src/Character/Commands/HoldPositionCommand.hpp

        src/Character/Commands/PatrolCommand.cpp
        src/Character/Commands/PatrolCommand.hpp

        src/Character/Commands/DestroyCommand.cpp
        src/Character/Commands/DestroyCommand.hpp

        src/Resource/Resource.cpp
        src/Resource/Resource.hpp

        src/Animation/Animation.cpp
        src/Animation/Animation.hpp

        src/Animation/BuildingAnimation.cpp
        src/Animation/BuildingAnimation.hpp

        src/Animation/ExplosionAnimation.cpp
        src/Animation/ExplosionAnimation.hpp

        src/Animation/CharacterAnimation.cpp
        src/Animation/CharacterAnimation.hpp

        src/Cursor/Cursor.cpp
        src/Cursor/Cursor.hpp

        src/TextureHolder/TextureHolder.cpp
        src/TextureHolder/TextureHolder.hpp

        src/Logger/Logger.cpp
        src/Logger/Logger.hpp

        src/Logger/LoggerImpl.cpp
        src/Logger/LoggerImpl.hpp

        src/Logger/ConsoleLogger.cpp
        src/Logger/ConsoleLogger.hpp

        src/Logger/FileLogger.cpp
        src/Logger/FileLogger.hpp

        src/Logger/SocketLogger.cpp
        src/Logger/SocketLogger.hpp

        src/Building/Commands/BuildingCommand.cpp
        src/Building/Commands/BuildingCommand.hpp

        src/Building/Commands/DestroyBuildingCommand.cpp
        src/Building/Commands/DestroyBuildingCommand.hpp

        src/Building/Commands/CreateBuildingCommand.cpp
        src/Building/Commands/CreateBuildingCommand.hpp

        src/Explosion/Explosion.cpp
        src/Explosion/Explosion.hpp)

add_executable(tiho ${SOURCE_FILES})

set(EXECUTABLE_NAME ${PROJECT_NAME})

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

# detect and add SFML to the project
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()










