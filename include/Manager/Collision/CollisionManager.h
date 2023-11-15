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

    class CollisionManager : public sf::NonCopyable {
      private:
        static Manager::Collision::CollisionStrategyFactory* m_pCollisionFactory;
        sf::FloatRect m_intersectionRect;
        EntityList* m_players;
        EntityList* m_staticEntities;
        EntityList* m_dynamicEntities;

      private:
        void applyCollision(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionType type, float overlap);
        bool verifyOverlap(std::pair<Entities::Entity*, Entities::Entity*> entities);
        void verifyCollisionStatic(Entities::Entity* entity);
        void verifyCollisionDynamic(Entities::Entity* entity, List<Entities::Entity*>::Iterator it);
      
      public:
        CollisionManager();
        ~CollisionManager();
        void setPlayersList(EntityList* playersList);
        void setStaticEntities(EntityList* staticList);
        void setDynamicEntities(EntityList* dynamicList);
        void verifyCollisions();
        CollisionStrategy* getCollisionStrategy(StrategyId id);
    };
  }
}

#endif