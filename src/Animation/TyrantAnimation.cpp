/* Main Include */
#include "Animation/TyrantAnimation.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Utility/Constants.h"

namespace Animations {
  TyrantAnimation::TyrantAnimation(Entities::Entity* pEntity, float timePerFrame) 
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  TyrantAnimation::~TyrantAnimation() {

  }

  void TyrantAnimation::changeFrame(const float deltaTime, TyrantFrames firstFrame, TyrantFrames lastFrame) {
    m_totalTime += deltaTime;
    if (m_totalTime >= m_timePerFrame) {
      m_currentFrame++;
      if (m_currentFrame < firstFrame || m_currentFrame > lastFrame)
        m_currentFrame = firstFrame;

      m_totalTime -= m_timePerFrame;
      m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
    }
  }

  void TyrantAnimation::update(const float deltaTime) {
    Entities::Characters::Tyrant* pTyrant = dynamic_cast<Entities::Characters::Tyrant*>(m_pEntity);

    if (pTyrant->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Dead);
    else if (pTyrant->getIsMidAir())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Jump);
    else if (pTyrant->getIsCharging())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Charge);
    else if (pTyrant->getIsLanding())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Land);
    else if (pTyrant->getIsShooting())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Shoot);
    else if (m_pEntity->getVelocity().x == 0.f)
      changeFrame(deltaTime, TyrantFrames::Idle1, TyrantFrames::Idle4);
    else
      changeFrame(deltaTime, TyrantFrames::Walk1, TyrantFrames::Walk4);

    m_pEntity->setTextureRect(m_textureRect);
  }
}