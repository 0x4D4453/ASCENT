#ifndef BOUNCECOLLISION_H
#define BOUNCECOLLISION_H

/* Program Defined */
#include "Manager/Collision/DefaultCollision.h"

namespace Manager {
  namespace Collision {
    class BounceCollision : public DefaultCollision {
      private:
        const float m_bounceMultiplier;
        
      public:
        BounceCollision();
        ~BounceCollision();
        
        virtual void applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif