/* Main Include */
#include "Animation/PlayerAnimation.h"

/* Program Defined */
#include "Entities/Entity.h"

namespace Animations {
  PlayerAnimation::PlayerAnimation(Entities::Entity* pEntity, float timePerFrame)
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  PlayerAnimation::~PlayerAnimation() {

  }

  void PlayerAnimation::update(const float deltaTime, bool isJumping, bool isCharging, bool isStaggered, const sf::Vector2f velocity) {
    // TODO: Staggered
    if (isCharging)
      m_textureRect.left = 64;
    else if (isJumping)
      m_textureRect.left = 80;
    else if (velocity.x == 0.f)
      m_textureRect.left = 0;
    else {
      m_totalTime += deltaTime;
      if (m_totalTime >= m_timePerFrame) {
        m_totalTime -= m_timePerFrame;
        m_textureRect.left = 16 * m_currentFrame;
        ++m_currentFrame;
        if (m_currentFrame > static_cast<int>(PlayerFrames::Walk3))
          m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
      }
    }
    m_pEntity->setTextureRect(m_textureRect);
  }
} 
