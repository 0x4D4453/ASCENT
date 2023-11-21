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
        bool m_isCharging;
        bool m_isJumping;

      private:
        virtual void doAction();
        void definePlayer();
        void followPlayer(const float speedMultiplier = 1.f);
        void stomping();
        void checkJumpDistance();
        void chargeJump();
        void jump();
        void checkLanding();
        void setIsCharging(const bool is);

      public:
        TyrantFollowingState(Tyrant* pTyrant = NULL, Stages::Stage* pStage = NULL);
        ~TyrantFollowingState();

        virtual void movementPattern();
    };
  }
}

#endif