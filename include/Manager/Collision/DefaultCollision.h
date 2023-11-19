#ifndef DEFAULTCOLLISION_H
#define DEFAULTCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

namespace Manager {
  namespace Collision {
    class DefaultCollision : public CollisionStrategy {
      private:
        const float m_friction;

      private:
        void applyFriction(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, sf::Vector2f* velocity);

      public:
        DefaultCollision();
        ~DefaultCollision();
        
        virtual void collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif