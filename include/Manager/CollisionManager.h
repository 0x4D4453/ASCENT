#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Forward Declaration */
class EntityList;
namespace Entities { class Entity; class Player; }

enum class CollisionType {
  Vertical,
  Horizontal
};

namespace Manager {
  class CollisionManager : sf::NonCopyable {
    private:
      Entities::Entity* m_pEntity;
      EntityList* m_pPlayers;
      EntityList* m_pObstacles;
      EntityList* m_pEnemies;

    private:
      void verifyOverlap(Entities::Entity* entity);
    
    public:
      CollisionManager();
      ~CollisionManager();
      void setPlayersList(EntityList* playersList);
      void setObstaclesList(EntityList* obstaclesList);
      void setEnemiesList(EntityList* enemiesList);
      void verifyCollisionObstacles();
      void verifyCollisionEnemies();
      void verifyCollision(Entities::Entity* entity);
  };
}

#endif