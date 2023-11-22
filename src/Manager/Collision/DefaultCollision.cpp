/* Main Include */
#include "Manager/Collision/DefaultCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Manager {
  namespace Collision {
    DefaultCollision::DefaultCollision(const float friction)
      : CollisionStrategy(0)
      , m_friction(friction)
    {

    }

    DefaultCollision::~DefaultCollision() {

    }

    sf::Vector2f DefaultCollision::getFriction(sf::Vector2f velocity) {
      const float speed = fabs(velocity.x);

      if (velocity.x > 0)
        velocity.x -= m_friction * m_dt;
      else if (velocity.x < 0)
        velocity.x += m_friction * m_dt;

      if (speed < 0.1f)
        velocity.x = 0.f;
      
      return velocity;
    }

    void DefaultCollision::collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static)
        return;

      if (type == CollisionType::Horizontal) {
        pOtherEntity->move(sf::Vector2f(overlap, 0));
      } else {
        sf::Vector2f velocity = pOtherEntity->getVelocity();
        if (velocity.y < 0) {
          if (pOtherEntity->getPosition().y >= pOwnEntity->getPosition().y)
            velocity.y = 0.f;
        } else {
          if (pOtherEntity->getPosition().y <= pOwnEntity->getPosition().y) {
            velocity = getFriction(velocity);
            pOtherEntity->move(pOwnEntity->getVelocity());
            pOtherEntity->setIsStaggered(false);
            velocity.y = 0.f;
          }
        }

        pOtherEntity->setVelocity(velocity);
        pOtherEntity->move(sf::Vector2f(0, overlap));
      }
    }
  }
}