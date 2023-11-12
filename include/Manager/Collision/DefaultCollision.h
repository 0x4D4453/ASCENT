#ifndef DEFAULTCOLLISION_H
#define DEFAULTCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class DefaultCollision : public CollisionStrategy {
      public:
        DefaultCollision();
        ~DefaultCollision();
        
        virtual void collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap);
    };
  }
}

#endif