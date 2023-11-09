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

    private:
      void checkCollision(Entities::Entity* pEntity, Entities::Player* pPlayer);
      void verifyCollisionPlatforms();
    
    public:
      CollisionManager();
      ~CollisionManager();
      void setPlayersList(EntityList* playersList);
      void setPlatformsList(EntityList* platformsList);
      void exec();
  };
}

#endif