#ifndef TIHO_GAME_HPP
#define TIHO_GAME_HPP

#include <cmath>
#include <string>
#include <list>

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

#include "../Character/Entity.hpp"
#include "../Character/Car.hpp"
#include "../Character/Tank.hpp"

#include "../Animation/Animation.hpp"

class Game : public IObject {
public:
    Game();
    ~Game();

    void createObjects();
    void run();

    sf::Texture& getBackground();
    sf::Texture& getCarTexture();
    sf::Texture& getTankTexture();

private:
    sf::RenderWindow m_window;
    std::list <Entity *> m_objects;

    sf::Texture m_tBackground;
    sf::Texture m_tCar;
    sf::Texture m_tTank;

    sf::Sprite m_sBackground;

    Animation m_animTank;
    Animation m_animCar;

    long m_amountTanks;
};

#endif //TIHO_GAME_HPP
