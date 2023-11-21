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
        const float m_stompDistance;
        const float m_jumpHeight;
        const float m_totalStompTime;
        const float m_stompDelay;
        Player* m_pPlayer;
        float m_elapsedStompTime;
        bool m_isStomping;
        bool m_isJumping;

      private:
        virtual void doAction();
        void definePlayer();
        void followPlayer();
        void checkStomp();
        void chargeStomp();
        void jump();
        void checkLanding();
        void setIsStomping(const bool is);

      public:
        TyrantFollowingState(Tyrant* pTyrant = NULL, EntityList* pPlayers = NULL);
        ~TyrantFollowingState();

        virtual void movementPattern();
    };
  }
}

#endif