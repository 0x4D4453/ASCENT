/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/Player.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Manager::GraphicsManager* TyrantState::m_pGraphicsManager(Manager::GraphicsManager::getInstance());
    const float TyrantState::m_dt(TyrantState::m_pGraphicsManager->getTimePerFrame()->asSeconds());

    TyrantState::TyrantState(Tyrant* pTyrant, Stages::Stage* pStage, const float timeLimit, const float moveTimeLimit)
      : m_id(TyrantStateID::Idle)
      , m_nextState(TyrantStateID::Jumping)
      , m_pStage(pStage)
      , m_pTyrant(pTyrant)
      , m_pPlayer(NULL)
      , m_pPlayers(pStage->getPlayers())
      , m_viewShake(m_pGraphicsManager->getView())
      , m_followDistance(1000.f)
      , m_moveTimeLimit(moveTimeLimit)
      , m_timeLimit(timeLimit)
      , m_moveTimeElapsed(0.f)
      , m_timeElapsed(0.f)
      , m_isReadyToChange(false)
      , m_isMoving(true)
    {

    }

    TyrantState::~TyrantState() {
      m_pTyrant = NULL;
      m_pPlayer = NULL;
      m_pPlayers = NULL;
      m_pStage = NULL;
    }

    const TyrantStateID TyrantState::getId() const {
      return m_id;
    }

    const bool TyrantState::getIsMoving() const {
      return m_isMoving;
    }

    void TyrantState::update(const float timeElapsed) {
      m_moveTimeElapsed += m_dt;
      if (m_moveTimeElapsed >= m_moveTimeLimit) {
        m_isMoving = false;
        doAction();
      }

      m_timeElapsed += timeElapsed;
      if (m_timeElapsed >= m_timeLimit && m_isReadyToChange)
        changeState(m_nextState);
    }

    void TyrantState::changeState(TyrantStateID id) {
      if (m_isReadyToChange)
        m_pTyrant->changeState(id);
    }

    void TyrantState::changeTyrantSpeed(const float speed, const float maxSpeed, const float timePerFrame) {
      m_pTyrant->setSpeed(speed);
      m_pTyrant->changeMaxSpeed(maxSpeed);
      m_pTyrant->getAnimation()->setTimePerFrame(timePerFrame);
    }

    void TyrantState::definePlayer() {
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
    void TyrantState::followPlayer(const float speedMultiplier, const float maxSpeedMultiplier) {
      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      sf::Vector2f tyrantVelocity = m_pTyrant->getVelocity();
      const float maxSpeed = m_pTyrant->getMaxSpeed() * maxSpeedMultiplier;

      if (playerPosition.x - m_pTyrant->getPosition().x > 0.f) {
        tyrantVelocity.x += m_pTyrant->getSpeed() * speedMultiplier * m_dt;

        if (tyrantVelocity.x > maxSpeed)
          tyrantVelocity.x = maxSpeed;
      } else {
        tyrantVelocity.x -= m_pTyrant->getSpeed() * speedMultiplier * m_dt;

        if (tyrantVelocity.x < -maxSpeed)
          tyrantVelocity.x = -maxSpeed;
      } 

      m_pTyrant->setVelocity(tyrantVelocity);
    }

    void TyrantState::stomp() {
      m_isMoving = true;

      int frame = m_pTyrant->getAnimation()->getCurrentFrame();
      if (frame == Animations::TyrantAnimation::TyrantFrames::Walk2 || frame == Animations::TyrantAnimation::TyrantFrames::Walk4) {
        if (!m_viewShake.finished(0.3f))
          m_viewShake.shake(m_dt, 15.f, 0.1f);
      } else {
        m_viewShake.reset();
      }
    }

    void TyrantState::movementPattern() {
      
    }
  }
}