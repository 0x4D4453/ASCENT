#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Forward Declaration */
class EntityList;
namespace Entities { class Player; }

namespace Manager {
  class CollisionManager : sf::NonCopyable {
    private:  
      Entities::Player* m_pPlayer1;
      EntityList* m_pPlatforms;
    
    public:
      CollisionManager();
      ~CollisionManager();
      void setPlayer(Entities::Player* player);
      void setPlatformsList(EntityList* platformsList);
      void verifyCollisionPlatforms();
  };
}

#endif