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

  void TyrantAnimation::changeFrame(const float deltaTime, int firstFrame, int lastFrame) {
    m_totalTime += deltaTime;
    if (m_totalTime >= m_timePerFrame) {
      if (m_currentFrame < firstFrame || m_currentFrame > lastFrame)
        m_currentFrame = firstFrame;

      m_totalTime -= m_timePerFrame;
      m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
      ++m_currentFrame;
    }
  }

  void TyrantAnimation::update(const float deltaTime) {
    Entities::Characters::Tyrant* pTyrant = dynamic_cast<Entities::Characters::Tyrant*>(m_pEntity);

    if (pTyrant->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Dead);
    else if (m_pEntity->getVelocity().x == 0.f)
      changeFrame(deltaTime, static_cast<int>(TyrantFrames::Idle1), static_cast<int>(TyrantFrames::Idle4));
    else
      changeFrame(deltaTime, static_cast<int>(TyrantFrames::Walk1), static_cast<int>(TyrantFrames::Walk4));

    m_pEntity->setTextureRect(m_textureRect);
  }
}