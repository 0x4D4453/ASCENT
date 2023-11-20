/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/Player.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    TyrantState::TyrantState(Tyrant* pTyrant, EntityList* pPlayers)
      : m_id(TyrantStateID::Idle)
      , m_pTyrant(pTyrant)
      , m_pPlayers(pPlayers)
      , m_timeLimit(50.f)
      , m_timeElapsed(0.f)
    {

    }

    TyrantState::~TyrantState() {
      m_pTyrant = NULL;
      m_pPlayers = NULL;
    }

    const TyrantStateID TyrantState::getId() const {
      return m_id;
    }

    void TyrantState::updateTime(const float timeElapsed) {
      m_timeElapsed += timeElapsed;

      if (m_timeElapsed >= m_timeLimit)
        changeState();
    }

    void TyrantState::changeState() {
      m_pTyrant->changeState(TyrantStateID::Following);
    }
  }
}