/* Main Include */
#include "Manager/Collision/DefaultCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    DefaultCollision::DefaultCollision()
      : CollisionStrategy(0.5f)
    {

    }

    DefaultCollision::~DefaultCollision() {

    }

    void DefaultCollision::collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static)
        return;

      if (type == CollisionType::Horizontal) {
        pOtherEntity->move(sf::Vector2f(overlap, 0));
      } else {
        pOtherEntity->setVelocity(sf::Vector2f(pOtherEntity->getVelocity().x, 0.f));
        pOtherEntity->move(sf::Vector2f(0, overlap));
      }
    }
  }
}