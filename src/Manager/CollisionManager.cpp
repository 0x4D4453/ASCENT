/* Main Include */
#include "Manager/CollisionManager.h"

/* Program Defined */
#include "Entities/EntityList.h"
#include "Entities/Player.h"
#include "Utility/List.h"

/* Standard Library */
#include <algorithm>

namespace Manager {
  CollisionManager::CollisionManager()
    : m_pPlatforms(NULL)
    , m_pPlayer1(NULL)
  {

  }

  CollisionManager::~CollisionManager() {
    m_pPlatforms = NULL;
    m_pPlayer1 = NULL;
  }

  void CollisionManager::setPlayer(Entities::Player* player) {
    if (player)
      m_pPlayer1 = player;
  }

  void CollisionManager::setPlatformsList(EntityList* platformsList) {
    if (platformsList)
      m_pPlatforms = platformsList;
  }

  /* DO NOT use intersects from SFML */

  void CollisionManager::verifyCollisionPlatforms() {
    sf::FloatRect playerBounds = m_pPlayer1->getGlobalBounds();
    float playerLeft = playerBounds.left;
    float playerRight = playerBounds.left + playerBounds.width;
    float playerTop = playerBounds.top;
    float playerBottom = playerBounds.top + playerBounds.width;

    List<Entities::Entity*>::Iterator it = m_pPlatforms->first();

    while (it != m_pPlatforms->last()) {
      sf::FloatRect platformBounds = (*it)->getGlobalBounds();
      float platformLeft = platformBounds.left;
      float platformRight = platformLeft + platformBounds.width;
      float platformTop = platformBounds.top;
      float platformBottom = platformBounds.top + platformBounds.height;

      float xOverlap = std::max(0.f, std::min(playerRight, platformRight) - std::max(playerLeft, platformLeft));
      float yOverlap =  std::max(0.f, std::min(playerBottom, platformBottom) - std::max(playerTop, platformTop));
        
      if (xOverlap || yOverlap) {
        if (yOverlap != 0 && yOverlap < xOverlap) {
            if (playerTop < platformTop) {
              yOverlap *= -1;
              m_pPlayer1->setIsJumping(false);
              m_pPlayer1->setVelocity(sf::Vector2f(0.f, 0.f));
            }
            m_pPlayer1->move(sf::Vector2f(0, yOverlap));
        } else if (xOverlap != 0 && xOverlap < yOverlap) {
            if (playerLeft < platformLeft)
              xOverlap *= -1;
            m_pPlayer1->move(sf::Vector2f(xOverlap, 0));
        }
      }
      ++it;
    }
  }
}