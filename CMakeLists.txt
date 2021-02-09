cmake_minimum_required(VERSION 3.10)
project(tiho)

set(CMAKE_CXX_STANDARD 11)
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

        src/Animation/Animation.cpp
        src/Animation/Animation.hpp

        src/IObject/IObject.hpp
        src/IObject/IObject.cpp

        src/Game/Game.cpp
        src/Game/Game.hpp

        src/Map/Map.cpp
        src/Map/Map.hpp

        src/Game/GameState.cpp
        src/Game/GameState.hpp

        src/Factory/CharacterFactory.hpp

        src/Factory/TankFactory.cpp
        src/Factory/TankFactory.hpp

        src/Factory/CarFactory.cpp
        src/Factory/CarFactory.hpp

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
        src/Game/LostState.hpp)

add_executable(tiho ${SOURCE_FILES})

set(EXECUTABLE_NAME ${PROJECT_NAME})

# If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

# detect and add SFML to the project
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()










