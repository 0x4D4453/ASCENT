/* Main Include */
#include "Animation/PlayerAnimation.h"

/* Program Defined */
#include "Entities/Entity.h"

#include <iostream>

namespace Animations {
  PlayerAnimation::PlayerAnimation(Entities::Entity* pEntity, float timePerFrame)
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
  }

  PlayerAnimation::~PlayerAnimation() {

  }

  void PlayerAnimation::update(const float deltaTime, bool isJumping, bool isCharging, bool isStaggered, const sf::Vector2f velocity) {
    if (isStaggered)
      m_pEntity->setTexture(m_animationFrames[static_cast<int>(PlayerFrames::Stagger)]);
    else if (isCharging)
      m_pEntity->setTexture(m_animationFrames[static_cast<int>(PlayerFrames::Charge)]);
    else if (isJumping)
      m_pEntity->setTexture(m_animationFrames[static_cast<int>(PlayerFrames::Jump)]);
    else if (m_pEntity->getVelocity().x == 0.f)
      m_pEntity->setTexture(m_animationFrames[static_cast<int>(PlayerFrames::Idle)]);
    else {
      m_totalTime += deltaTime;

      if (m_totalTime >= m_timePerFrame) {
        m_totalTime -= m_timePerFrame;
        m_pEntity->setTexture(m_animationFrames[m_currentFrame]);
        ++m_currentFrame;
        if (m_currentFrame > static_cast<int>(PlayerFrames::Walk3))
          m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
      }
      
    }
  }
} 
