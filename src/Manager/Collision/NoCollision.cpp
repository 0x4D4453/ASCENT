/* Main Include */
#include "Manager/Collision/NoCollision.h"

/* Program Defined */
#include "Manager/Collision/CollisionManager.h"
#include "Entities/Entity.h"

namespace Manager {
  namespace Collision {
    NoCollision::NoCollision()
      : CollisionStrategy()
    {

    }

    NoCollision::~NoCollision() {

    }

    void NoCollision::collide(Entities::Entity *pOwnEntity, Entities::Entity *pOtherEntity, CollisionType type, float overlap) {

    }
  }
}