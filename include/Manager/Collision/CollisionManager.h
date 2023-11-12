#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategyFactory.h"

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
        Entities::Entity* m_pEntity;
        EntityList* m_pPlayers;
        EntityList* m_pObstacles;
        EntityList* m_pEnemies;

      private:
        void verifyOverlap(Entities::Entity* entity);
        void verifyCollisionObstacles();
        void verifyCollisionEnemies();
      
      public:
        CollisionManager();
        ~CollisionManager();
        void setPlayersList(EntityList* playersList);
        void setObstaclesList(EntityList* obstaclesList);
        void setEnemiesList(EntityList* enemiesList);
        void verifyCollision(Entities::Entity* entity);
        CollisionStrategy* getCollisionStrategy(StrategyId id);
    };
  }
}

#endif