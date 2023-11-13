/* Main Include */
#include "Animation/PlayerAnimation.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Utility/Constants.h"

namespace Animations {
  PlayerAnimation::PlayerAnimation(Entities::Entity* pEntity, float timePerFrame)
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
  }

  PlayerAnimation::~PlayerAnimation() {

  }

  void PlayerAnimation::update(const float deltaTime, Entities::Player* pPlayer) {
    if (pPlayer->getIsStaggered())
      m_textureRect.left = Constants::SPRITE_SIZE * 6;
    else if (pPlayer->getIsCharging())
      m_textureRect.left = Constants::SPRITE_SIZE * 4;
    else if (pPlayer->getIsJumping())
      m_textureRect.left = Constants::SPRITE_SIZE * 5;
    else if (pPlayer->getVelocity().x == 0.f)
      m_textureRect.left = 0;
    else {
      m_totalTime += deltaTime;
      if (m_totalTime >= m_timePerFrame) {
        m_totalTime -= m_timePerFrame;
        m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
        ++m_currentFrame;
        if (m_currentFrame > static_cast<int>(PlayerFrames::Walk3))
          m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
      }
    }
    m_pEntity->setTextureRect(m_textureRect);
  }
} 
