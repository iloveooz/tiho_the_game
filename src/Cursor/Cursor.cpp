#include "Cursor.hpp"

namespace ControlGame {
    Cursor::Cursor(sf::Sprite sprite) : m_sprite(sprite), m_bVisible(false) {}

    Cursor::~Cursor() {

    }

    void Cursor::setVisible(bool value) {
        m_bVisible = value;
    }

    bool Cursor::getVisible() const {
        return m_bVisible;
    }

    void Cursor::setSprite(sf::Sprite& sprite) {
        m_sprite = sprite;
    }

    sf::Sprite& Cursor::getSprite() {
        return m_sprite;
    }

    void Cursor::update() {
            m_rect.setSize(sf::Vector2f(m_sprite.getTexture()->getSize().x, m_sprite.getTexture()->getSize().y));
            m_rect.setPosition(m_sprite.getPosition().x - m_sprite.getTexture()->getSize().x / 2,
                               m_sprite.getPosition().y - m_sprite.getTexture()->getSize().y / 2);
            m_rect.setFillColor(sf::Color::Transparent);
            m_rect.setOutlineThickness(1);
            m_rect.setOutlineColor(sf::Color::Cyan);
    }

    void Cursor::draw(sf::RenderWindow &app) {
        if (m_bVisible) {
            app.draw(m_rect);
        }
    }
}
