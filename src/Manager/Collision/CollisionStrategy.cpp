/* Main Include */
#include "Manager/Collision/CollisionStrategy.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    CollisionStrategy::CollisionStrategy()
      : m_delay(0)
    {

    }

    CollisionStrategy::~CollisionStrategy() {

    }

    const float CollisionStrategy::getDelay() const {
      return m_delay;
    }
  }
}