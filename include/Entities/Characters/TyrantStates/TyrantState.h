#ifndef TYRANTSTATE_H
#define TYRANTSTATE_H

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "Entities/EntityList.h"
#include "Utility/ViewShake.h"
#include "Stage/Stage.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    /* Forward Declaration */
    class Tyrant;
    class Player;

    enum TyrantStateID {
      Idle,
      Jumping,
      Shooting,
      Neutralized
    };

    class TyrantState {
      protected:
        static Manager::GraphicsManager* m_pGraphicsManager;
        static const float m_dt;
        TyrantStateID m_id;
        TyrantStateID m_nextState;
        Stages::Stage* m_pStage;
        Tyrant* m_pTyrant;
        Player* m_pPlayer;
        EntityList* m_pPlayers;
        ViewShake m_viewShake;
        const float m_followDistance;
        const float m_moveTimeLimit;
        const float m_timeLimit;
        float m_moveTimeElapsed;
        float m_timeElapsed;
        bool m_isReadyToChange;
        bool m_isMoving;

      protected:
        virtual void doAction() = 0;
        void changeState(TyrantStateID id);
        void changeTyrantSpeed(const float speed, const float maxSpeed, const float timePerFrame);
        void definePlayer();
        void followPlayer(const float speedMultiplier = 1.f, const float maxSpeedMultiplier = 1.f);
        void stomp();

      public:
        TyrantState(Tyrant* pTyrant = NULL, Stages::Stage* pStage = NULL, const float timeLimit = 5.f, const float moveTimeLimit = 5.f);
        ~TyrantState();

        void update(const float timeElapsed);
        const TyrantStateID getId() const;
        const bool getIsMoving() const;

        virtual void movementPattern();

        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif