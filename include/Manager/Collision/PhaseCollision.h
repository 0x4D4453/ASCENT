#ifndef PHASECOLLISION_H
#define PHASECOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class PhaseCollision : public CollisionStrategy {
      private:
        const float m_drag;

      private:
        const float applyDrag(Entities::Entity *pOwnEntity, const float component);

      public:
        PhaseCollision();
        ~PhaseCollision();
        
        virtual void reactToCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif