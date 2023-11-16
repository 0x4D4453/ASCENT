/* Main Include */
#include "Manager/Collision/KnockbackCollision.h"

/* Program Defined */
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    KnockbackCollision::KnockbackCollision()
      : CollisionStrategy(1.f)
      , m_maxForce(5.f)
    {

    }

    KnockbackCollision::~KnockbackCollision() {

    }

    void KnockbackCollision::collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap) {
      if (otherEntity->getEntityType() == Entities::EntityType::Static)
        return;
      
      float knockback = ownEntity->getKnockback();
      if (knockback > m_maxForce)
        knockback = m_maxForce;
      
      if (otherEntity->getPosition().x < ownEntity->getPosition().x)
        otherEntity->setVelocity(sf::Vector2f(-knockback, -knockback));
      else
        otherEntity->setVelocity(sf::Vector2f(knockback, -knockback));

      otherEntity->setIsStaggered(true);
    }
  }
}