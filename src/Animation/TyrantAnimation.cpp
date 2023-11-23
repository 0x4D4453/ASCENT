/* Main Include */
#include "Animation/TyrantAnimation.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/TyrantStates/TyrantJumpingState.h"
#include "Entities/Characters/TyrantStates/TyrantShootingState.h"
#include "Utility/Constants.h"

namespace Animations {
  TyrantAnimation::TyrantAnimation(Entities::Entity* pEntity, float timePerFrame) 
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  TyrantAnimation::~TyrantAnimation() {

  }

  void TyrantAnimation::update(const float deltaTime) {
    using namespace Entities::Characters;

    Tyrant* pTyrant = dynamic_cast<Tyrant*>(m_pEntity);

    if (pTyrant->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Neutralized);
    else if (pTyrant->getIsMidAir())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Jump);
    else if (m_pEntity->getVelocity().x != 0.f && pTyrant->getState()->getIsMoving())
      changeFrame(deltaTime, TyrantFrames::Walk1, TyrantFrames::Walk4);
    else if (pTyrant->getState()->getId() == TyrantStateID::Jumping) {
      TyrantJumpingState* state = dynamic_cast<TyrantJumpingState*>(pTyrant->getState());
      if (state->getIsCharging())
        m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Charge);
      if (state->getIsLanding())
        m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Land);
    }
    else if (pTyrant->getState()->getId() == TyrantStateID::Shooting) {
      TyrantShootingState* state = dynamic_cast<TyrantShootingState*>(pTyrant->getState());
      if (state->getIsShooting())
        m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Shoot);
    } else
      changeFrame(deltaTime, TyrantFrames::Idle1, TyrantFrames::Idle4);

    m_pEntity->setTextureRect(m_textureRect);
  }
}