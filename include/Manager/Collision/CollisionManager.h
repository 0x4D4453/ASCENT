#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategyFactory.h"
#include "Utility/List.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Forward Declaration */
class EntityList;
namespace Entities { class Entity; }

namespace Manager {
  namespace Collision {
    enum class CollisionType {
      Vertical,
      Horizontal
    };

    struct CollisionInfo {
      CollisionType type;
      float overlap;
    };

    class CollisionManager : public sf::NonCopyable {
      private:
        static Manager::Collision::CollisionStrategyFactory* m_pCollisionFactory;
        sf::FloatRect m_intersectionRect;
        EntityList* m_pPlayers;
        EntityList* m_pStaticEntities;
        EntityList* m_pDynamicEntities;

      private:
        void applyCollision(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionInfo* info);
        void applyCollisionReaction(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionInfo* info);
        void verifyOverlap(std::pair<Entities::Entity*, Entities::Entity*> entities);
        void verifyCollisionStatic(Entities::Entity* pEntity);
        void verifyCollisionDynamic(Entities::Entity* pEntity, List<Entities::Entity*>::Iterator it);
      
      public:
        CollisionManager();
        ~CollisionManager();
        void setPlayersList(EntityList* pPlayersList);
        void setStaticEntities(EntityList* pStaticList);
        void setDynamicEntities(EntityList* pDynamicList);
        void verifyCollisions();
        CollisionStrategy* getCollisionStrategy(StrategyId id);
    };
  }
}

#endif