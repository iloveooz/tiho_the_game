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

    void run();

    sf::Texture& getBackground() const;
    sf::Texture& getCarTexture() const;
    sf::Texture& getTankTexture() const;

private:
    void createObjects();
    void updateObjects();
    void renderObjects();

    void processEvents();

    void handlePlayerEvent(sf::Keyboard::Key key, bool isPressed);

    sf::RenderWindow m_window;
    std::list <Entity *> m_objects;

    sf::Texture m_tBackground;
    sf::Texture m_tCar;
    sf::Texture m_tTank;

    sf::Sprite m_sBackground;

    Animation m_animTank;
    Animation m_animCar;

    bool m_isMovingUp;
    bool m_isMovingDown;
    bool m_isMovingLeft;
    bool m_isMovingRight;

    long m_amountTanks;
};

#endif //TIHO_GAME_HPP
