/* Main Include */
#include "Manager/CollisionManager.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"
#include "Utility/List.h"

/* Standard Library */
#include <iostream>
#include <algorithm>

namespace Manager {
  CollisionManager::CollisionManager()
    : m_pPlatforms(NULL)
    , m_pPlayers(NULL)
  {

  }

  CollisionManager::~CollisionManager() {
    m_pPlatforms = NULL;
    m_pPlayers = NULL;
  }

  void CollisionManager::setPlayersList(EntityList* playersList) {
    if (playersList)
      m_pPlayers = playersList;
  }

  void CollisionManager::setPlatformsList(EntityList* platformsList) {
    if (platformsList)
      m_pPlatforms = platformsList;
  }

  /* DO NOT use intersects from SFML */

  void CollisionManager::verifyCollisionPlatforms() {
    using namespace Entities;

    List<Entity*>::Iterator platformIterator = m_pPlatforms->first();

    while (platformIterator != m_pPlatforms->last()) {
      Entity::Coordinates platformCoordinates = (*platformIterator)->getCoordinates();

      List<Entity*>::Iterator playerIterator = m_pPlayers->first();

      while (playerIterator != m_pPlayers->last()) {
        Player* player = static_cast<Player*>((*playerIterator));
        Entity::Coordinates playerCoordinates = player->getCoordinates();

        float xOverlap = std::max(0.f, std::min(playerCoordinates.right, platformCoordinates.right) 
                        - std::max(playerCoordinates.left, platformCoordinates.left));
        float yOverlap = std::max(0.f, std::min(playerCoordinates.bottom, platformCoordinates.bottom) 
                        - std::max(playerCoordinates.top, platformCoordinates.top));

        if (xOverlap || yOverlap) {
          if (yOverlap != 0 && yOverlap < xOverlap) {
            if (playerCoordinates.top < platformCoordinates.top) {
              yOverlap *= -1;
              player->setIsJumping(false);
              player->setVelocity(sf::Vector2f(0.f, 0.f));
            }
            player->move(sf::Vector2f(0, yOverlap));
          } else if (xOverlap != 0 && xOverlap < yOverlap) {
            if (playerCoordinates.left < platformCoordinates.left)
              xOverlap *= -1;
            player->move(sf::Vector2f(xOverlap, 0));
          }
        }

        ++playerIterator;
      }
      
      ++platformIterator;
    }
  }
}