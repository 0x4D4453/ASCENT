/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantJumpingState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"

namespace Entities {
  namespace Characters {
    TyrantJumpingState::TyrantJumpingState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 25.f)
      , m_jumpDistance(500.f)
      , m_jumpHeight(300.f)
      , m_chargeTimeLimit(1.5f)
      , m_chargeTimeElapsed(0.f)
      , m_isCharging(false)
      , m_isJumping(false)
      , m_isLanding(false)
    {
      m_id = TyrantStateID::Jumping;
      m_nextState = TyrantStateID::Shooting;
      changeTyrantSpeed(25.f, 0.5f, 0.4f);
    }

    TyrantJumpingState::~TyrantJumpingState() {

    }

    void TyrantJumpingState::checkJumpDistance() {
      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      sf::Vector2f tyrantPosition = m_pTyrant->getPosition();

      if (fabs(playerPosition.x - tyrantPosition.x) <= m_jumpDistance && fabs(playerPosition.y - tyrantPosition.y) <= m_followDistance) {
        m_isReadyToChange = false;
        m_isCharging = true;
      }
    }

    void TyrantJumpingState::chargeJump() {
      m_viewShake.reset();
      m_chargeTimeElapsed += m_dt;
      if (m_chargeTimeElapsed >= m_chargeTimeLimit) {
        m_isCharging = false;
        jump();

        m_chargeTimeElapsed = 0.f;
      }
    }

    void TyrantJumpingState::jump() {
      m_pTyrant->setVelocity(sf::Vector2f(0.f, -sqrt(2 * m_jumpHeight * m_dt * Constants::GRAVITY)));
      m_pTyrant->setIsMidAir(true);
      m_isJumping = true;
    }

    void TyrantJumpingState::checkLanding() {
      if (m_pTyrant->getIsMidAir()) {
        followPlayer(1.f, 7.5f);
        return;
      }

      m_isLanding = true;
      if (!m_viewShake.finished(1.5f)) {
        m_viewShake.shake(m_dt, 15.f, 0.15f);
      } else {
        m_viewShake.reset();
        m_isJumping = false;
        m_isLanding = false;
        m_isReadyToChange = true;
        m_moveTimeElapsed = 0.f;
      }
    }

    const bool TyrantJumpingState::getIsCharging() const {
      return m_isCharging;
    }

    const bool TyrantJumpingState::getIsLanding() const {
      return m_isLanding;
    }

    void TyrantJumpingState::movementPattern() {
      if (m_isJumping || m_isCharging)
        return;

      definePlayer();

      if (!m_pPlayer) {
        changeState(TyrantStateID::Idle);
        return;
      }

      followPlayer();
      stomp();
    }


    void TyrantJumpingState::doAction() {
      if (m_isJumping) {
        checkLanding();
        return;
      }

      if (m_isCharging) {
        chargeJump();
        return;
      }
      
      if (m_pPlayer)
        checkJumpDistance();
    }
  }
}