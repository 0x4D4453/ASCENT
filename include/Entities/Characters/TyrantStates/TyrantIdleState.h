#ifndef TYRANTIDLESTATE_H
#define TYRANTIDLESTATE_H

/* Program Defined */
#include "Entities/Characters/TyrantStates/TyrantState.h"

namespace Entities {
  namespace Characters {
    class TyrantIdleState : public TyrantState {
      private:
        const float m_healing;
        const float m_healCooldown;
        float m_timeSinceHeal;

      private:
        virtual void doAction();
        void heal();

      public:
        TyrantIdleState(Tyrant* pTyrant = NULL, EntityList* pPlayers = NULL);
        ~TyrantIdleState();

        virtual void movementPattern();
    };
  }
}

#endif