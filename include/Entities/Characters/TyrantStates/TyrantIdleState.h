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
        void heal();

      public:
        TyrantIdleState(Tyrant* pTyrant = NULL, Stages::Stage* pStage = NULL);
        ~TyrantIdleState();
        virtual void doAction();

        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif