#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

/* Forward Declaration */
namespace Entities { namespace Characters { class Player; } }

namespace Animations {
  class PlayerAnimation : public Animation {
    public:
      enum PlayerFrames {
        Idle = 0,
        Walk1 = 1,
        Walk2,
        Walk3,
        Charge,
        Jump,
        Stagger,
        JumpStraight,
        Neutralized,
      };

    private:
      Entities::Characters::Player* m_pPlayer;
      bool m_isStraight;

    private:
      void updateJump(const float deltaTime);

    public:
      PlayerAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~PlayerAnimation();
      void update(const float deltaTime);
  };
}

#endif