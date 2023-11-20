/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantIdleState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"

namespace Entities {
  namespace Characters {
    TyrantIdleState::TyrantIdleState(Tyrant* pTyrant, EntityList* pPlayers)
      : TyrantState(pTyrant, pPlayers)
      , m_healing(5.f)
      , m_healCooldown(1.f)
    {
      m_id = TyrantStateID::Idle;
    }

    TyrantIdleState::~TyrantIdleState() {

    }

    void TyrantIdleState::heal() {
      const float health = m_pTyrant->getHealthPoints();
      if (health >= m_pTyrant->getMaxHealthPoints())
        return;

      m_timeSinceHeal += m_timeElapsed;
      if (m_timeSinceHeal > m_healCooldown) {
        m_pTyrant->setColor(sf::Color::Green);
        m_pTyrant->setHealthPoints(health + m_healing);
      }
    }

    void TyrantIdleState::movementPattern() {
      
    }


    void TyrantIdleState::doAction() {
      heal();
    }
  }
}