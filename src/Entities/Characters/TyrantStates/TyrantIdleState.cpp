/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantIdleState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"

namespace Entities {
  namespace Characters {
    TyrantIdleState::TyrantIdleState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 5.f, 0.f)
      , m_healing(0.75f)
      , m_healCooldown(0.5f)
      , m_timeSinceHeal(0.f)
    {
      m_id = TyrantStateID::Idle;
      m_nextState = TyrantStateID::Jumping;
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
      if (m_pPlayer)
        m_isReadyToChange = true;

      heal();
    }

    void TyrantIdleState::save(nlohmann::ordered_json& jsonData) {
      TyrantState::save(jsonData);
      jsonData["state"]["timeSinceHeal"] = m_timeSinceHeal;
    }

    void TyrantIdleState::loadSave(const nlohmann::ordered_json& jsonData) {
      TyrantState::loadSave(jsonData);
      m_timeSinceHeal = jsonData["state"]["timeSinceHeal"].template get<float>();
    }
  }
}