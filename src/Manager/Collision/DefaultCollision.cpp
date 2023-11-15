/* Main Include */
#include "Manager/Collision/DefaultCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    DefaultCollision::DefaultCollision()
      : CollisionStrategy()
    {

    }

    DefaultCollision::~DefaultCollision() {

    }

    void DefaultCollision::collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap) {
      if (otherEntity->getEntityType() == Entities::EntityType::Static)
        return;

      if (type == CollisionType::Horizontal) {
        otherEntity->move(sf::Vector2f(overlap, 0));
      } else {
        otherEntity->move(sf::Vector2f(0, overlap));
        
        if (ownEntity->getPosition().y >= otherEntity->getPosition().y)
          otherEntity->setVelocity(sf::Vector2f(0.f, 0.f));
        else
          otherEntity->setVelocity(sf::Vector2f(otherEntity->getVelocity().x * .5f, 0.f));
      }
    }
  }
}