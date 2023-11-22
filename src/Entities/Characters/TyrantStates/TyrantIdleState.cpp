/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantIdleState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"

namespace Entities {
  namespace Characters {
    TyrantIdleState::TyrantIdleState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 10.f, 0.f)
      , m_healing(0.75f)
      , m_healCooldown(1.5f)
      , m_timeSinceHeal(0.f)
    {
      m_id = TyrantStateID::Idle;
      m_nextState = TyrantStateID::Jumping;
      m_isReadyToChange = true;
      changeTyrantSpeed(25.f, 0.5f, 0.8f);
    }

    TyrantIdleState::~TyrantIdleState() {

    }

    void TyrantIdleState::heal() {
      const float health = m_pTyrant->getHealthPoints();
      if (health >= m_pTyrant->getMaxHealthPoints())
        return;

      m_timeSinceHeal += m_dt;
      if (m_timeSinceHeal > m_healCooldown) {
        m_pTyrant->setColor(sf::Color::Green);
        m_pTyrant->setHealthPoints(health + m_healing);
        m_timeSinceHeal = 0.f;
      }
    }

    void TyrantIdleState::doAction() {
      heal();
    }
  }
}