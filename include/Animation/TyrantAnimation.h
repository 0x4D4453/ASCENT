#ifndef TYRANTANIMATION_H
#define TYRANTANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

namespace Animations {
  class TyrantAnimation : public Animation {
    public:
      enum TyrantFrames {
        Idle1 = 0,
        Idle2,
        Walk1 = 2,
        Walk2,
        Walk3,
        Walk4,
        Charge,
        Jump,
        Dead,
      };

    private:
      void changeFrame(const float deltaTime, int firstFrame, int lastFrame);

    public:
      TyrantAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~TyrantAnimation();
      void update(const float deltaTime);
  };
}

#endif