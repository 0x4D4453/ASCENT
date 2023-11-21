/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantFollowingState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/Player.h"

namespace Entities {
  namespace Characters {
    TyrantFollowingState::TyrantFollowingState(Tyrant* pTyrant, EntityList* pPlayers)
      : TyrantState(pTyrant, pPlayers, 10.f)
      , m_followDistance(500.f)
      , m_stompDistance(300.f)
      , m_jumpHeight(500.f)
      , m_totalStompTime(3.f)
      , m_stompDelay(5.f)
      , m_pPlayer(NULL)
      , m_elapsedStompTime(0.f)
      , m_isCharging(false)
      , m_isJumping(false)
    {
      m_id = TyrantStateID::Following;
      definePlayer();
    }

    TyrantFollowingState::~TyrantFollowingState() {
      m_pPlayer = NULL;
    }

    void TyrantFollowingState::definePlayer() {
      List<Entity*>::Iterator it = m_pPlayers->first();
      sf::Vector2f tyrantPosition = m_pTyrant->getPosition();
      float minDistance = m_followDistance;

      while (it != m_pPlayers->last()) {
        sf::Vector2f playerPosition = (*it)->getPosition();
        float distance = fabs(playerPosition.x - tyrantPosition.x);
        if (distance <= minDistance && fabs(playerPosition.y - tyrantPosition.y) <= m_followDistance) {
          m_pPlayer = dynamic_cast<Player*>(*it);
          minDistance = distance;
        }

        ++it;
      }
    }

    // Código altamente baseado no código do monitor Giovane
    void TyrantFollowingState::followPlayer(const float speedMultiplier) {
      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      sf::Vector2f tyrantVelocity = m_pTyrant->getVelocity();

      if (playerPosition.x - m_pTyrant->getPosition().x > 0.f)
        tyrantVelocity.x = m_pTyrant->getSpeed() * speedMultiplier * m_dt;
      else 
        tyrantVelocity.x = -m_pTyrant->getSpeed() * speedMultiplier * m_dt;

      m_pTyrant->setVelocity(tyrantVelocity);
    }

    void TyrantFollowingState::stomping() {
      int frame = m_pTyrant->getCurrentFrame();
      if (frame == Animations::TyrantAnimation::TyrantFrames::Walk2 || frame == Animations::TyrantAnimation::TyrantFrames::Walk4) {
        if (!m_viewShake.finished(0.3f))
          m_viewShake.shake(m_dt, 15.f, 0.1f);
      } else {
        m_viewShake.reset();
      }
    }

    void TyrantFollowingState::checkJumpDistance() {
      if (m_elapsedStompTime < m_stompDelay)
        return;

      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      sf::Vector2f tyrantPosition = m_pTyrant->getPosition();

      if (fabs(playerPosition.x - tyrantPosition.x) <= m_stompDistance && fabs(playerPosition.y - tyrantPosition.y) <= m_followDistance) {
        m_elapsedStompTime = 0.f;
        m_isReadyToChange = false;
        setIsCharging(true);
      }
    }

    void TyrantFollowingState::chargeJump() {
      m_elapsedStompTime += m_dt;
      if (m_elapsedStompTime >= m_totalStompTime) {
        setIsCharging(false);
        jump();

        m_elapsedStompTime = 0.f;
      }
    }

    void TyrantFollowingState::jump() {
      m_pTyrant->setVelocity(sf::Vector2f(0.f, -sqrt(2 * m_jumpHeight * m_dt * Constants::GRAVITY)));
      m_pTyrant->setIsMidAir(true);
      m_isJumping = true;
    }

    void TyrantFollowingState::checkLanding() {
      if (m_pTyrant->getIsMidAir()) {
        followPlayer(10.f);
        return;
      }

      m_pTyrant->setIsLanding(true);
      if (!m_viewShake.finished(3.f)) {
        m_viewShake.shake(m_dt, 15.f, 0.15f);
      } else {
        m_isJumping = false;
        m_viewShake.reset();
        m_pTyrant->setIsLanding(false);
        m_isReadyToChange = true;
      }
    }

    void TyrantFollowingState::setIsCharging(const bool is) {
      m_pTyrant->setIsCharging(is);
      m_isCharging = is;
    }

    void TyrantFollowingState::movementPattern() {
      if (m_isJumping || m_isCharging)
        return;

      definePlayer();

      if (!m_pPlayer)
        return;

      followPlayer();
      stomping();
    }


    void TyrantFollowingState::doAction() {
      if (m_isJumping) {
        checkLanding();
        return;
      }

      if (m_isCharging) {
        chargeJump();
        return;
      }
      
      m_elapsedStompTime += m_dt;
      checkJumpDistance();
    }
  }
}