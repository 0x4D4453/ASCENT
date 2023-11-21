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
      , m_pPlayer(NULL)
    {
      m_id = TyrantStateID::Following;
      definePlayer();
    }

    TyrantFollowingState::~TyrantFollowingState() {
      m_pPlayer = NULL;
    }

    void TyrantFollowingState::definePlayer() {
      List<Entity*>::Iterator it = m_pPlayers->first();
      sf::Vector2f tyrantPostion = m_pTyrant->getPosition();
      float minDistance = m_followDistance;

      while (it != m_pPlayers->last()) {
        sf::Vector2f playerPosition = (*it)->getPosition();
        float distance = fabs(playerPosition.x - tyrantPostion.x);
        if (distance <= minDistance && fabs(playerPosition.y - tyrantPostion.y) <= m_followDistance) {
          m_pPlayer = dynamic_cast<Player*>(*it);
          minDistance = distance;
        }

        ++it;
      }
    }

    // Código altamente baseado no código do monitor Giovane
    void TyrantFollowingState::movementPattern() {
      definePlayer();

      if (!m_pPlayer)
        return;

      sf::Vector2f playerPosition = m_pPlayer->getPosition();
      sf::Vector2f tyrantVelocity = m_pTyrant->getVelocity();

      if (playerPosition.x - m_pTyrant->getPosition().x > 0.f)
        tyrantVelocity.x = m_pTyrant->getSpeed() * m_dt;
      else 
        tyrantVelocity.x = -m_pTyrant->getSpeed() * m_dt;

      m_pTyrant->setVelocity(tyrantVelocity);

      int frame = m_pTyrant->getCurrentFrame();
      std::cout << frame << std::endl;

      if (frame == Animations::TyrantAnimation::TyrantFrames::Walk2 || frame == Animations::TyrantAnimation::TyrantFrames::Walk4) {
        if (!m_viewShake.finished(0.5f))
          m_viewShake.shake(m_dt, 20.f, 0.1f);
      } else {
        m_viewShake.reset();
      }
    }


    void TyrantFollowingState::doAction() {

    }
  }
}