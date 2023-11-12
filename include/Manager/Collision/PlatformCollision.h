#ifndef PLATFORMCOLLISION_H
#define PLATFORMCOLLISION_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

/* Forward Declaration */
namespace Entities { class Player; }

namespace Manager {
  namespace Collision {
    class PlatformCollision : public CollisionStrategy {
      private:
        void playerCollide(Entities::Player *player, CollisionType type);

      public:
        PlatformCollision();
        ~PlatformCollision();
        
        virtual void collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap);
    };
  }
}

#endif