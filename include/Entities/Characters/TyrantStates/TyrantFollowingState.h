#ifndef TYRANTFOLLOWINGSTATE_H
#define TYRANTFOLLOWINGSTATE_H

/* Program Defined */
#include "Entities/Characters/TyrantStates/TyrantState.h"

namespace Entities {
  namespace Characters {
    /* Forward Declaration */
    class Player;

    class TyrantFollowingState : public TyrantState {
      private:
        const float m_followDistance;
        Player* m_pPlayer;

      private:
        virtual void doAction();
        void definePlayer();

      public:
        TyrantFollowingState(Tyrant* pTyrant = NULL, EntityList* pPlayers = NULL);
        ~TyrantFollowingState();

        virtual void movementPattern();
    };
  }
}

#endif