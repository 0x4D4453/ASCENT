#ifndef DEFAULTCOLLISION_H
#define DEFAULTCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"
#include "Utility/Constants.h"

namespace Manager {
  namespace Collision {
    class DefaultCollision : public CollisionStrategy {
      protected:
        const float m_friction;

      protected:
        sf::Vector2f getFriction(sf::Vector2f velocity);

      public:
        DefaultCollision(const float friction = Constants::DRAG * 15.0f);
        ~DefaultCollision();
        
        virtual void applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap);
    };
  }
}

#endif