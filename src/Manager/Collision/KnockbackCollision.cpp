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

    void KnockbackCollision::collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static)
        return;
      
      float knockback = pOwnEntity->getKnockback();
      if (knockback > m_maxForce)
        knockback = m_maxForce;
      
      if (pOtherEntity->getCenteredPosition().x < pOwnEntity->getCenteredPosition().x)
        pOtherEntity->setVelocity(sf::Vector2f(-knockback, -knockback));
      else
        pOtherEntity->setVelocity(sf::Vector2f(knockback, -knockback));

      pOtherEntity->setIsStaggered(true);
    }
  }
}