#ifndef NOCOLLISION_H
#define NOCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class NoCollision : public CollisionStrategy {
      public:
        NoCollision();
        ~NoCollision();
        
        virtual void collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif