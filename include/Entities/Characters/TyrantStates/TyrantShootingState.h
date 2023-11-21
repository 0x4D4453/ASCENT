#ifndef TYRANTSHOOTINGSTATE_H
#define TYRANTSHOOTINGSTATE_H

/* Program Defined */
#include "Entities/Characters/TyrantStates/TyrantState.h"

/* Standard Library */
#include <vector> 

namespace Entities {
  namespace Characters {
    class TyrantShootingState : public TyrantState {
      private:
        std::vector<sf::Vector2f> m_shootingSpots;
        const float m_timeBetweenShots;
        const float m_shootingAngle;
        const float m_shootingSpeed;
        float m_timeSinceLastShot;
        int m_currentSpot;

      private:
        virtual void doAction();
        void shoot();

      public:
        TyrantShootingState(Tyrant* pTyrant = NULL, Stages::Stage* pStage = NULL);
        ~TyrantShootingState();

        virtual void movementPattern();
    };
  }
}

#endif