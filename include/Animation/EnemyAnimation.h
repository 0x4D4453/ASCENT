#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

namespace Animations {
  class EnemyAnimation : public Animation {
    public:
      enum DefaultFrames {
        Walk1 = 1,
        Walk2
      };

    public:
      EnemyAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~EnemyAnimation();
      void update(const float deltaTime);
  };
}

#endif