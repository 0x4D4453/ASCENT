#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

/* Forward Declaration */
namespace Entities { class Player; }

namespace Animations {
  class PlayerAnimation : public Animation {
    public:
      enum PlayerFrames {
        Walk1 = 1,
        Walk2,
        Walk3
      };

    public:
      PlayerAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~PlayerAnimation();
      void update(const float deltaTime, Entities::Player* pPlayer);
  };
}

#endif