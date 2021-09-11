#include "Animation.hpp"

namespace Animations {
    Animation::Animation() {
        m_dFrame = 0.0;
        m_dSpeed = 0.0;
    }

    void Animation::update() {
        m_dFrame += m_dSpeed;
        size_t n = m_vFrames.size();
        if (m_dFrame >= n)
            m_dFrame -= n;
        if (n > 0)
            m_sprite.setTextureRect(m_vFrames[int(m_dFrame)]);
    }

    bool Animation::isEnd() {
        return m_dFrame + m_dSpeed >= m_vFrames.size();
    }
}
