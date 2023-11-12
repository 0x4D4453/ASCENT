#ifndef PLAYERCOLLISION_H
#define PLAYERCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class PlayerCollision : public CollisionStrategy {
      public:
        PlayerCollision();
        ~PlayerCollision();
        
        virtual void collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap);
    };
  }
}

#endif