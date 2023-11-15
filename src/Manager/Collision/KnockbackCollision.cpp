/* Main Include */
#include "Manager/Collision/KnockbackCollision.h"

/* Program Defined */
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    KnockbackCollision::KnockbackCollision()
      : CollisionStrategy()
      , m_force(2.5f)
    {

    }

    KnockbackCollision::~KnockbackCollision() {

    }

    void KnockbackCollision::collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap) {
      if (otherEntity->getEntityType() == Entities::EntityType::Static)
        return;
      
      if (otherEntity->getPosition().x < ownEntity->getPosition().x)
        otherEntity->setVelocity(sf::Vector2f(-m_force, -m_force));
      else
        otherEntity->setVelocity(sf::Vector2f(m_force, -m_force));

      otherEntity->setIsStaggered(true);
    }
  }
}