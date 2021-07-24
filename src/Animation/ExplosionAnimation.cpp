#include "ExplosionAnimation.hpp"

namespace Animations {
    ExplosionAnimation::ExplosionAnimation() {}

    ExplosionAnimation::~ExplosionAnimation() {}

    ExplosionAnimation::ExplosionAnimation(sf::Texture &t, int wBorder, int hBorder) {
        m_sprite.setTexture(t);
        m_sprite.setOrigin(wBorder / 2, hBorder / 2);
    }

    void ExplosionAnimation::setTexture(sf::Texture &texture, ExplodeType type) {
        // Big explosion    (texture, 0, 0, 256, 256, 48, 0.4);
        // Middle explosion (texture, 0, 0, 192, 192, 64, 0.5);
        // Small explosion  (texture, 0, 0, 50, 50, 20, 0.6);

        m_dFrame = 0;

        int x = 0;
        int y = 0;

        int w = 0;
        int h = 0;
        int count = 0;

        switch (type) {
            case ExplodeType::BigExplode:
                m_dSpeed = 0.4;
                w = 256;
                h = 256;
                count = 48;
            break;

            case ExplodeType::MiddleExplode:
                m_dSpeed = 0.5;
                w = 192;
                h = 192;
                count = 64;
            break;

            case ExplodeType::SmallExplode:
                m_dSpeed = 0.6;
                w = 50;
                h = 50;
                count = 20;
            break;
        }

        for (int i = 0; i < count; i++)
            m_vFrames.emplace_back(x + i * w, y, w, h);

        m_sprite.setTexture(texture);
        m_sprite.setOrigin(w / 2, h / 2);
        m_sprite.setTextureRect(m_vFrames[0]);
    }

    bool ExplosionAnimation::isEnd() {
        return m_dFrame + m_dSpeed >= m_vFrames.size();
    }

    void ExplosionAnimation::update() {
        m_dFrame += m_dSpeed;
        int n = m_vFrames.size();
        if (m_dFrame >= n)
            m_dFrame -= n;
        if (n > 0)
            m_sprite.setTextureRect(m_vFrames[int(m_dFrame)]);
    }

    sf::Sprite& ExplosionAnimation::getSprite() {
        return m_sprite;
    }
}