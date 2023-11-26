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
    , m_pTyrant(dynamic_cast<Entities::Characters::Tyrant*>(m_pEntity))
    , m_state(Entities::Characters::TyrantStateID::Idle)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  TyrantAnimation::~TyrantAnimation() {
    m_pTyrant = NULL;
  }

  void TyrantAnimation::chooseUpdate(const float deltaTime) {
    using namespace Entities::Characters;
    
    switch (m_state) {
      case TyrantStateID::Jumping:
        jumpingUpdate(deltaTime);
        break;
      case TyrantStateID::Shooting:
        shootingUpdate(deltaTime);
        break;
      default:
        break;
    }
  }

  void TyrantAnimation::jumpingUpdate(const float deltaTime) {
    using namespace Entities::Characters;

    TyrantJumpingState* state = dynamic_cast<TyrantJumpingState*>(m_pTyrant->getState());
    if (state->getIsCharging())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Charge);
    if (state->getIsLanding())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Land);
  }

  void TyrantAnimation::shootingUpdate(const float deltaTime) {
    using namespace Entities::Characters;
    
    TyrantShootingState* state = dynamic_cast<TyrantShootingState*>(m_pTyrant->getState());
    if (state->getIsShooting())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Shoot);
  }

  void TyrantAnimation::update(const float deltaTime) {
    if (m_pTyrant->getIsMidAir())
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Jump);
    else if (m_pEntity->getVelocity().x != 0.f && m_pTyrant->getState()->getIsMoving())
      changeFrame(deltaTime, TyrantFrames::Walk1, TyrantFrames::Walk4);
    else
      changeFrame(deltaTime, TyrantFrames::Idle1, TyrantFrames::Idle4);

    m_state = m_pTyrant->getState()->getId();
    chooseUpdate(deltaTime);

    if (m_pTyrant->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(TyrantFrames::Neutralized);

    m_pEntity->setTextureRect(m_textureRect);
  }
}