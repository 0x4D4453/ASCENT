/* Main Include */
#include "Manager/Collision/DefaultCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Manager {
  namespace Collision {
    DefaultCollision::DefaultCollision()
      : CollisionStrategy(0)
      , m_friction(Constants::DRAG * 15.0f)
    {

    }

    DefaultCollision::~DefaultCollision() {

    }

    void DefaultCollision::applyFriction(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, sf::Vector2f* velocity) {
      const float speed = velocity->x > 0 ? velocity->x : -velocity->x;

      if (velocity->x > 0)
        velocity->x -= m_friction * m_dt;
      else if (velocity->x < 0)
        velocity->x += m_friction * m_dt;

      if (speed < 0.1f)
        velocity->x = 0.f;

      pOtherEntity->move(pOwnEntity->getVelocity());
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
            applyFriction(pOwnEntity, pOtherEntity, &velocity);
            velocity.y = 0.f;
          }
        }

        pOtherEntity->setVelocity(velocity);
        pOtherEntity->move(sf::Vector2f(0, overlap));
      }
    }
  }
}