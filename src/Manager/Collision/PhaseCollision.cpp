/* Main Include */
#include "Manager/Collision/PhaseCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Manager {
  namespace Collision {
    PhaseCollision::PhaseCollision()
      : CollisionStrategy()
      , m_drag(0.1f)
    {

    }

    PhaseCollision::~PhaseCollision() {

    }

    const float PhaseCollision::applyDrag(Entities::Entity *pOwnEntity, const float component) {
      if (component > 0)
        return component - m_drag * m_dt;

      if (component < 0)
        return component + m_drag * m_dt;

      if (fabs(component) < 0.1f)
        return 0.f;

      return component;
    }

    void PhaseCollision::applyCollision(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {
      sf::Vector2f velocity = pOtherEntity->getVelocity();
      velocity.x = applyDrag(pOtherEntity, velocity.x);
      velocity.y = applyDrag(pOtherEntity, velocity.y);
      
      pOtherEntity->setVelocity(velocity);
    }
  }
}