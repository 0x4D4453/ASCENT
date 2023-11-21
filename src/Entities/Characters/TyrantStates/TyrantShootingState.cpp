/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantShootingState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Projectile.h"
#include "Utility/Constants.h"

namespace Entities {
  namespace Characters {
    TyrantShootingState::TyrantShootingState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 10.f)
      , m_shootingSpots()
      , m_timeBetweenShots(1.25f)
      , m_shootingAngle(60.f)
      , m_shootingSpeed(25.f)
      , m_timeSinceLastShot(0.f)
      , m_currentSpot(0)
    {
      m_id = TyrantStateID::Shooting;
      m_nextState = TyrantStateID::Idle;
      m_isReadyToChange = true;

      m_shootingSpots.push_back(sf::Vector2f(Constants::SPRITE_SIZE * 5, Constants::SPRITE_SIZE * 3));
      m_shootingSpots.push_back(sf::Vector2f(Constants::SPRITE_SIZE * -5, Constants::SPRITE_SIZE * 3));
    }

    TyrantShootingState::~TyrantShootingState() {

    }

    void TyrantShootingState::shoot() {
      m_timeSinceLastShot += m_dt;
      if (m_timeSinceLastShot > m_timeBetweenShots) {
        if (m_currentSpot >= m_shootingSpots.size())
          m_currentSpot = 0;

        sf::Vector2f position = sf::Vector2f(m_pTyrant->getPosition() + m_shootingSpots[m_currentSpot]);
        float angle = m_shootingSpots[m_currentSpot].x > 0 ? m_shootingAngle : 180 - m_shootingAngle;
        m_pStage->spawnProjectile(Textures::Projectile, position, Constants::SCALE * 2.0f, m_shootingSpeed, angle);

        m_timeSinceLastShot = 0.f;
        m_currentSpot++;
      }
    }

    void TyrantShootingState::movementPattern() {
      
    }


    void TyrantShootingState::doAction() {
      shoot();
    }
  }
}