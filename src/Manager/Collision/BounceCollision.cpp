/* Main Include */
#include "Manager/Collision/BounceCollision.h"

/* Program Defined */
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    BounceCollision::BounceCollision()
      : DefaultCollision(Constants::DRAG * 3.f)
      , m_bounceMultiplier(0.75f)
    {

    }

    BounceCollision::~BounceCollision() {

    }

    void BounceCollision::applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static)
        return;
      
      sf::Vector2f velocity = pOtherEntity->getVelocity();
      if (type == CollisionType::Horizontal) {
        pOtherEntity->move(sf::Vector2f(overlap, 0));
        velocity.x = -velocity.x * m_bounceMultiplier;
      } else {
        velocity = getFriction(velocity);
        pOtherEntity->move(sf::Vector2f(0, overlap));
        velocity.y = -velocity.y * m_bounceMultiplier;
      }

      pOtherEntity->setVelocity(velocity);
    }
  }
}