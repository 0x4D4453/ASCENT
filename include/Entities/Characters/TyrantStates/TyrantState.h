#ifndef TYRANTSTATE_H
#define TYRANTSTATE_H

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "Entities/EntityList.h"

namespace Entities {
  namespace Characters {
    /* Forward Declaration */
    class Tyrant;

    enum TyrantStateID {
      Idle,
      Following,
      Charging,
      Jumping,
      Launching,
      Dead
    };

    class TyrantState {
      protected:
        static Manager::GraphicsManager* m_pGraphicsManager;
        static const float m_dt;
        TyrantStateID m_id;
        TyrantStateID m_nextState;
        Tyrant* m_pTyrant;
        EntityList* m_pPlayers;
        const float m_timeLimit;
        float m_timeElapsed;

      private:
        virtual void doAction() = 0;
        void changeState(TyrantStateID id);

      public:
        TyrantState(Tyrant* pTyrant = NULL, EntityList* pPlayers = NULL, const float timeLimit = 5.f);
        ~TyrantState();

        void update(const float timeElapsed);
        const TyrantStateID getId() const;

        virtual void movementPattern() = 0;
    };
  }
}

#endif