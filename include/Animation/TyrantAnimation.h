#ifndef TYRANTANIMATION_H
#define TYRANTANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"
#include "Entities/Characters/TyrantStates/TyrantState.h"

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
      Entities::Characters::Tyrant* m_pTyrant;
      Entities::Characters::TyrantStateID m_state;

    private:
      void chooseUpdate(const float deltaTime);
      void jumpingUpdate(const float deltaTime);
      void shootingUpdate(const float deltaTime);

    public:
      TyrantAnimation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~TyrantAnimation();
      void update(const float deltaTime);
  };
}

#endif