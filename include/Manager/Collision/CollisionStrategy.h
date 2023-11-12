#ifndef COLLISIONSTRATEGY_H
#define COLLISIONSTRATEGY_H

/* Forward Declaration */
namespace Entities { class Entity; }

namespace Manager {
  namespace Collision {
    enum class CollisionType;

    class CollisionStrategy {
      public:
        CollisionStrategy();
        ~CollisionStrategy();
        
        virtual void collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap) = 0;
    };
  }
}

#endif