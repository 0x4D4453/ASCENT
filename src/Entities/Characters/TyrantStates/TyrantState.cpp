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

    TyrantState::TyrantState(Tyrant* pTyrant, Stages::Stage* pStage, const float timeLimit)
      : m_id(TyrantStateID::Idle)
      , m_nextState(TyrantStateID::Following)
      , m_pStage(pStage)
      , m_pTyrant(pTyrant)
      , m_pPlayers(pStage->getPlayers())
      , m_viewShake(m_pGraphicsManager->getView())
      , m_timeLimit(timeLimit)
      , m_timeElapsed(0.f)
      , m_isReadyToChange(false)
    {

    }

    TyrantState::~TyrantState() {
      m_pTyrant = NULL;
      m_pPlayers = NULL;
      m_pStage = NULL;
    }

    const TyrantStateID TyrantState::getId() const {
      return m_id;
    }

    void TyrantState::update(const float timeElapsed) {
      doAction();

      m_timeElapsed += timeElapsed;
      if (m_timeElapsed >= m_timeLimit && m_isReadyToChange)
        changeState(m_nextState);
    }

    void TyrantState::changeState(TyrantStateID id) {
      if (m_isReadyToChange)
        m_pTyrant->changeState(id);
    }

    void TyrantState::changeTyrantSpeed(const float speed) {
      m_pTyrant->setSpeed(speed);
      m_pTyrant->getAnimation()->setTimePerFrame(12.5f / speed);
    }
  }
}