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

    void KnockbackCollision::applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      if (pOtherEntity->getEntityType() == Entities::EntityType::Static || pOtherEntity->getIsKnockbackResistant())
        return;
      
      float knockback = pOwnEntity->getKnockback();
      if (knockback > m_maxForce)
        knockback = m_maxForce;
      
      if (pOtherEntity->getPosition().x < pOwnEntity->getPosition().x)
        pOtherEntity->setVelocity(sf::Vector2f(-knockback, -knockback));
      else
        pOtherEntity->setVelocity(sf::Vector2f(knockback, -knockback));

      pOtherEntity->setIsStaggered(true);
    }
  }
}