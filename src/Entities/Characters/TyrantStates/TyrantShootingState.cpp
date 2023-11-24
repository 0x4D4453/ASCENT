/* Main Include */
#include "Entities/Characters/TyrantStates/TyrantShootingState.h"

/* Program Defined */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Projectile.h"
#include "Utility/Constants.h"

namespace Entities {
  namespace Characters {
    TyrantShootingState::TyrantShootingState(Tyrant* pTyrant, Stages::Stage* pStage)
      : TyrantState(pTyrant, pStage, 20.f, 5.f)
      , m_shootingSpots()
      , m_timeBetweenShots(1.f)
      , m_shootingAngle(M_PI / 4)
      , m_angleRange(M_PI / 6)
      , m_shootingSpeed(7.5f)
      , m_shootingTimeLimit(5.f)
      , m_shootingTimeElapsed(0.f)
      , m_timeSinceLastShot(0.f)
      , m_currentSpot(0)
      , m_isShooting(false)
    {
      m_id = TyrantStateID::Shooting;
      m_nextState = TyrantStateID::Idle;
      m_isReadyToChange = true;
      changeTyrantSpeed(50.f, 1.75f, 0.2f);

      m_shootingSpots.push_back(sf::Vector2f(Constants::SPRITE_SIZE * 10, -Constants::SPRITE_SIZE * 2));
      m_shootingSpots.push_back(sf::Vector2f(-Constants::SPRITE_SIZE * 10, -Constants::SPRITE_SIZE * 2));
    }

    TyrantShootingState::~TyrantShootingState() {
      m_shootingSpots.clear();
    }

    void TyrantShootingState::shoot() {
      m_viewShake.reset();
      m_isReadyToChange = false;
      m_isShooting = true;

      m_timeSinceLastShot += m_dt;
      if (m_timeSinceLastShot > m_timeBetweenShots) {
        if (m_currentSpot >= m_shootingSpots.size())
          m_currentSpot = 0;

        sf::Vector2f position = sf::Vector2f(m_pTyrant->getPosition() + m_shootingSpots[m_currentSpot]);
        float angle = m_shootingAngle + rand() / (RAND_MAX / m_angleRange);

        if (m_shootingSpots[m_currentSpot].x <= 0)
          angle = M_PI - angle;

        m_pStage->spawnProjectile(Textures::Projectile, position, Constants::SCALE * 1.5f, m_shootingSpeed, angle);
        m_timeSinceLastShot = 0.f;
        m_currentSpot++;
      }

      m_shootingTimeElapsed += m_dt;
      if (m_shootingTimeElapsed >= m_shootingTimeLimit) {
        m_isReadyToChange = true;
        m_isShooting = false;
        m_shootingTimeElapsed = 0.f;
        m_moveTimeElapsed = 0.f;
      }
    }

    const bool TyrantShootingState::getIsShooting() const {
      return m_isShooting;
    }

    void TyrantShootingState::movementPattern() {
      if (m_isShooting)
        return;

      definePlayer();

      if (!m_pPlayer) {
        changeState(TyrantStateID::Idle);
        return;
      }

      followPlayer();
      stomp();
    }

    void TyrantShootingState::doAction() {
      shoot();
    }
  }
}