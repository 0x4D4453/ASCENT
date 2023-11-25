#ifndef TYRANTFOLLOWINGSTATE_H
#define TYRANTFOLLOWINGSTATE_H

/* Program Defined */
#include "Entities/Characters/TyrantStates/TyrantState.h"

namespace Entities {
  namespace Characters {
    class TyrantJumpingState : public TyrantState {
      private:
        const float m_jumpDistance;
        const float m_jumpHeight;
        const float m_chargeTimeLimit;
        float m_chargeTimeElapsed;
        bool m_isCharging;
        bool m_isJumping;
        bool m_isLanding;

      private:
        void checkJumpDistance();
        void chargeJump();
        void jump();
        void checkLanding();

      public:
        TyrantJumpingState(Tyrant* pTyrant = NULL, Stages::Stage* pStage = NULL);
        ~TyrantJumpingState();

        const bool getIsCharging() const;
        const bool getIsLanding() const;

        virtual void movementPattern();
        virtual void doAction();

        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif