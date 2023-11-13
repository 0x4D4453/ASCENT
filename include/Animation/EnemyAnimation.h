#ifndef ENEMYANIMATION_H
#define ENEMYANIMATION_H

/* Program Defined */
#include "Animation/Animation.h"

/* Forward Declaration */
namespace Entities { class Enemy; }

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
      void update(const float deltaTime, Entities::Enemy* pEnemy);
      void update(const float deltaTime, Entities::Enemy* pEnemy, const sf::Vector2f velocity);
  };
}

#endif