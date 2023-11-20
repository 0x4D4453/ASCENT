#ifndef TYRANTSTATE_H
#define TYRANTSTATE_H

/* Program Defined */
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
        TyrantStateID m_id;
        Tyrant* m_pTyrant;
        EntityList* m_pPlayers;
        const float m_timeLimit;
        float m_timeElapsed;

      private:
        void changeState();

      public:
        TyrantState(Tyrant* pTyrant = NULL, EntityList* pPlayers = NULL);
        ~TyrantState();

        void updateTime(const float timeElapsed);
        const TyrantStateID getId() const;

        virtual void movementPattern() = 0;
        virtual void doAction() = 0;
    };
  }
}

#endif