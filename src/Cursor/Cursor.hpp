#ifndef TIHO_CURSOR_HPP
#define TIHO_CURSOR_HPP

#include <SFML/Graphics.hpp>

#include "../IObject/IObject.hpp"

namespace ControlGame {

    class Cursor : public IObject {
    public:
        Cursor() = delete;
        explicit Cursor(sf::Sprite mSprite);

        virtual ~Cursor();

        void update();

        void setSprite(sf::Sprite& mSprite);
        sf::Sprite& getSprite();

        void draw(sf::RenderWindow &app);

        void setVisible(bool value);
        bool getVisible() const;

    protected:
        bool m_bVisible;

    private:
        sf::RectangleShape m_rect;
        sf::Sprite m_sprite;
    };

}

#endif //TIHO_CURSOR_HPP
