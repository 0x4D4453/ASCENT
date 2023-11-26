#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

/* Forward Declaration */
namespace Entities { namespace Characters { class Enemy; } }

namespace Animations {
  class EnemyAnimation : public Animation {
    private:
      Entities::Characters::Enemy* m_pEnemy;
      const MDirection m_mDirection;

    public:
      enum DefaultFrames {
        Idle = 0,
        Walk1 = 1,
        Walk2,
        Neutralized = 4,
      };

    public:
      EnemyAnimation(Entities::Entity* pEntity = NULL, MDirection direction = X, float timePerFrame = 0.1f);
      ~EnemyAnimation();
      void update(const float deltaTime);
  };
}

#endif