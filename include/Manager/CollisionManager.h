#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Forward Declaration */
class EntityList;
namespace Entities { class Entity; class Player; }

namespace Manager {
  class CollisionManager : sf::NonCopyable {
    private:  
      EntityList* m_pPlayers;
      EntityList* m_pPlatforms;
      EntityList* m_pEnemies;

    private:
      void checkCollision(Entities::Entity* pEntity, Entities::Player* pPlayer);
      void verifyCollisionEntities(EntityList* pEntityList);
    
    public:
      CollisionManager();
      ~CollisionManager();
      void setPlayersList(EntityList* playersList);
      void setPlatformsList(EntityList* platformsList);
      void setEnemiesList(EntityList* enemiesList);
      void exec();
  };
}

#endif