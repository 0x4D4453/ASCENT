/* Main Include */
#include "Animation/PlayerAnimation.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Characters/Player.h"
#include "Utility/Constants.h"

namespace Animations {
  PlayerAnimation::PlayerAnimation(Entities::Entity* pEntity, float timePerFrame)
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
  }

  PlayerAnimation::~PlayerAnimation() {

  }

  void PlayerAnimation::update(const float deltaTime) {
    Entities::Characters::Player* pPlayer = dynamic_cast<Entities::Characters::Player*>(m_pEntity);

    if (pPlayer->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Dead);
    else if (pPlayer->getIsStaggered())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Stagger);
    else if (pPlayer->getIsCharging())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Charge);
    else if (pPlayer->getIsJumping())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Jump);
    else if (pPlayer->getVelocity().x == 0.f)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Idle);
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
