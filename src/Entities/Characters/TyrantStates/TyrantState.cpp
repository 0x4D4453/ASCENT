/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/Player.h"
#include "Animation/TyrantAnimation.h"

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
      , m_viewShake(pStage->getViews())
      , m_followDistance(700.f)
      , m_moveTimeLimit(moveTimeLimit)
      , m_timeLimit(timeLimit)
      , m_moveTimeElapsed(0.f)
      , m_timeElapsed(0.f)
      , m_isReadyToChange(false)
      , m_isMoving(true)
    {

    }

    TyrantState::~TyrantState() {
      m_viewShake.reset();
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
      m_pPlayer = NULL;

      while (it != m_pPlayers->last()) {
        sf::Vector2f playerPosition = (*it)->getPosition();
        float distance = fabs(playerPosition.x - tyrantPosition.x);
        if (distance <= minDistance && fabs(playerPosition.y - tyrantPosition.y) <= m_followDistance / 2.5f) {
          m_pPlayer = dynamic_cast<Player*>(*it);
          minDistance = distance;
        }

        ++it;
      }
    }

    // Código baseado no código do monitor Giovane
    // https://www.youtube.com/playlist?list=PLR17O9xbTbIBBoL3lli44N8LdZVvg-_uZ
    void TyrantState::followPlayer(const float speedMultiplier, const float maxSpeedMultiplier) {
      sf::Vector2f tyrantVelocity = m_pTyrant->getVelocity();
      if (m_pPlayer->getIsColliding(m_pTyrant->getId())) {
        tyrantVelocity.x = 0.f;
        return;
      }

      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      const float maxSpeed = m_pTyrant->getMaxSpeed() * maxSpeedMultiplier;
      const float distance = playerPosition.x - m_pTyrant->getPosition().x;

      if (distance > 0.f) {
        tyrantVelocity.x += m_pTyrant->getSpeed() * speedMultiplier * m_dt;

        if (tyrantVelocity.x > maxSpeed)
          tyrantVelocity.x = maxSpeed;
      } else if (distance < 0.f) {
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
      definePlayer();
    }

    void TyrantState::save(nlohmann::ordered_json& jsonData) {
      jsonData["state"]["ID"] = m_id;
      jsonData["state"]["nextStateID"] = m_nextState;
      jsonData["state"]["moveTimeElapsed"] = m_moveTimeElapsed;
      jsonData["state"]["timeElapsed"] = m_timeElapsed;
      jsonData["state"]["isReadyToChange"] = m_isReadyToChange;
      jsonData["state"]["isMoving"] = m_isMoving;
    }

    void TyrantState::loadSave(const nlohmann::ordered_json& jsonData) {
      m_id = jsonData["state"]["ID"].template get<TyrantStateID>();
      m_nextState = jsonData["state"]["nextStateID"].template get<TyrantStateID>();
      m_moveTimeElapsed = jsonData["state"]["moveTimeElapsed"].template get<float>();
      m_timeElapsed = jsonData["state"]["timeElapsed"].template get<float>();
      m_isReadyToChange = jsonData["state"]["isReadyToChange"].template get<bool>();
      m_isMoving = jsonData["state"]["isMoving"].template get<bool>();
    }
  }
}