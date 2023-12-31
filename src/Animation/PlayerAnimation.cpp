/* Main Include */
#include "Animation/PlayerAnimation.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Characters/Player.h"
#include "Utility/Constants.h"

namespace Animations {
  PlayerAnimation::PlayerAnimation(Entities::Entity* pEntity, float timePerFrame)
    : Animation(pEntity, timePerFrame)
    , m_pPlayer(dynamic_cast<Entities::Characters::Player*>(pEntity))
    , m_isStraight(true)
  {
    m_currentFrame = static_cast<int>(PlayerFrames::Walk1);
  }

  PlayerAnimation::~PlayerAnimation() {
    m_pPlayer = NULL;
  }

  void PlayerAnimation::updateJump(const float deltaTime) {
    if (m_isStraight)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::JumpStraight);
    else
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Jump);
  }

  void PlayerAnimation::update(const float deltaTime) {
    if (m_pPlayer->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Neutralized);
    else if (m_pPlayer->getIsStaggered())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Stagger);
    else if (m_pPlayer->getIsCharging())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Charge);
    else if (m_pPlayer->getIsMidAir()) {
      m_isStraight = m_pPlayer->getVelocity().x == 0.f;
      updateJump(deltaTime);
    } else if (m_pPlayer->getVelocity().x == 0.f)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(PlayerFrames::Idle);
    else
      changeFrame(deltaTime, PlayerFrames::Walk1, PlayerFrames::Walk3);

    m_pEntity->setTextureRect(m_textureRect);
  }
} 
