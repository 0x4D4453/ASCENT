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
        sf::FloatRect m_intersectionRect;
        Entities::Entity* m_pEntity;
        EntityList* m_pPlayers;
        EntityList* m_pObstacles;
        EntityList* m_pEnemies;

      private:
        bool verifyOverlap(Entities::Entity* entity);
        bool verifyCollisionObstacles();
        bool verifyCollisionEnemies();
      
      public:
        CollisionManager();
        ~CollisionManager();
        void setPlayersList(EntityList* playersList);
        void setObstaclesList(EntityList* obstaclesList);
        void setEnemiesList(EntityList* enemiesList);
        bool verifyCollision(Entities::Entity* entity);
        CollisionStrategy* getCollisionStrategy(StrategyId id);
    };
  }
}

#endif