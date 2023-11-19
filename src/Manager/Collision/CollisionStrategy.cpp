/* Main Include */
#include "Manager/Collision/CollisionStrategy.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Manager {
  namespace Collision {
    const float CollisionStrategy::m_dt(Constants::FIXED_STEP);

    CollisionStrategy::CollisionStrategy(const float m_delay)
      : m_delay(m_delay)
    {

    }

    CollisionStrategy::~CollisionStrategy() {

    }

    const float CollisionStrategy::getDelay() const {
      return m_delay;
    }
  }
}