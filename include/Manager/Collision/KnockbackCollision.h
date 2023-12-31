#ifndef KNOCKBACKCOLLISION_H
#define KNOCKBACKCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class KnockbackCollision : public CollisionStrategy {
      private:
        const float m_maxForce;
        
      public:
        KnockbackCollision();
        ~KnockbackCollision();
        
        virtual void applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif