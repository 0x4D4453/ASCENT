#ifndef TYRANTANIMATION_H
#define TYRANTANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

/* Forward Declaration */
namespace Entities { namespace Characters { class Tyrant; } }

namespace Animations {
  class TyrantAnimation : public Animation {
    public:
      enum TyrantFrames {
        Idle1 = 0,
        Idle2,
        Idle3,
        Idle4,
        Walk1 = 4,
        Walk2,
        Walk3,
        Walk4,
        Charge,
        Jump,
        Land,
        Shoot,
        Neutralized
      };

    private:
      void jumpingUpdate(const float deltaTime, Entities::Characters::Tyrant* pTyrant);
      void shootingUpdate(const float deltaTime, Entities::Characters::Tyrant* pTyrant);

    public:
      TyrantAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~TyrantAnimation();
      void update(const float deltaTime);
  };
}

#endif