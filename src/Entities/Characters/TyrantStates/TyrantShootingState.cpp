/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantShootingState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Projectile.h"
#include "Utility/Constants.h"

namespace Entities {
  namespace Characters {
    TyrantShootingState::TyrantShootingState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 12.5f)
      , m_shootingSpots()
      , m_timeBetweenShots(0.25f)
      , m_shootingAngle(M_PI / 4)
      , m_angleRange(M_PI / 6)
      , m_shootingSpeed(7.f)
      , m_timeSinceLastShot(0.f)
      , m_currentSpot(0)
    {
      m_id = TyrantStateID::Shooting;
      m_nextState = TyrantStateID::Idle;
      m_isReadyToChange = true;
      changeTyrantSpeed(70.f);

      m_shootingSpots.push_back(sf::Vector2f(Constants::SPRITE_SIZE * 10, Constants::SPRITE_SIZE * 10));
      m_shootingSpots.push_back(sf::Vector2f(-Constants::SPRITE_SIZE * 10, Constants::SPRITE_SIZE * 10));
    }

    TyrantShootingState::~TyrantShootingState() {

    }

    void TyrantShootingState::shoot() {
      m_pTyrant->setIsShooting(true);
      m_isReadyToChange = false;

      m_timeSinceLastShot += m_dt;
      if (m_timeSinceLastShot > m_timeBetweenShots) {
        if (m_currentSpot >= m_shootingSpots.size())
          m_currentSpot = 0;

        sf::Vector2f position = sf::Vector2f(m_pTyrant->getPosition() + m_shootingSpots[m_currentSpot]);
        float angle = m_shootingAngle + rand() / (RAND_MAX / m_angleRange);

        if (m_shootingSpots[m_currentSpot].x <= 0)
          angle = M_PI - angle;

        m_pStage->spawnProjectile(Textures::Projectile, position, Constants::SCALE * 2.0f, m_shootingSpeed, angle);

        m_pTyrant->setIsShooting(false);
        m_isReadyToChange = true;
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