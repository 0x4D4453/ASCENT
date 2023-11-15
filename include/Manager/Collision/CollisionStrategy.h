#ifndef COLLISIONSTRATEGY_H
#define COLLISIONSTRATEGY_H

/* Forward Declaration */
namespace Entities { class Entity; }

namespace Manager {
  namespace Collision {
    enum class CollisionType;

    class CollisionStrategy {
      protected:
        const float m_delay;

      public:
        CollisionStrategy();
        ~CollisionStrategy();

        const float getDelay() const;
        
        virtual void collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, CollisionType type, float overlap) = 0;
    };
  }
}

#endif