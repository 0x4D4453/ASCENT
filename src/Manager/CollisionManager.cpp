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
    , m_pEnemies(NULL)
  {

  }

  CollisionManager::~CollisionManager() {
    m_pPlatforms = NULL;
    m_pPlayers = NULL;
    m_pEnemies = NULL;
  }

  void CollisionManager::setPlayersList(EntityList* playersList) {
    if (playersList)
      m_pPlayers = playersList;
  }

  void CollisionManager::setPlatformsList(EntityList* platformsList) {
    if (platformsList)
      m_pPlatforms = platformsList;
  }

  void CollisionManager::setEnemiesList(EntityList* enemiesList) {
    if (enemiesList)
      m_pEnemies = enemiesList;
  }

  void CollisionManager::checkCollision(Entities::Entity* pEntity, Entities::Player* pPlayer) {
    using namespace Entities;

    Entity::Coordinates entityCoordinates = pEntity->getCoordinates();
    Entity::Coordinates playerCoordinates = pPlayer->getCoordinates();

    float xOverlap = std::max(0.f, std::min(playerCoordinates.right, entityCoordinates.right) 
                    - std::max(playerCoordinates.left, entityCoordinates.left));
    float yOverlap = std::max(0.f, std::min(playerCoordinates.bottom, entityCoordinates.bottom) 
                    - std::max(playerCoordinates.top, entityCoordinates.top));

    if (yOverlap != 0 && yOverlap < xOverlap) {
      if (playerCoordinates.top < entityCoordinates.top) {
        yOverlap *= -1;
        pPlayer->setIsJumping(false);
        pPlayer->setVelocity(sf::Vector2f(0.f, 0.f));
      }
        pPlayer->move(sf::Vector2f(0, yOverlap));
    } else if (xOverlap != 0 && xOverlap < yOverlap) {
        if (playerCoordinates.left < entityCoordinates.left)
          xOverlap *= -1;
        pPlayer->move(sf::Vector2f(xOverlap, 0));
    }
  }

  void CollisionManager::verifyCollisionEntities(EntityList* pEntityList) {
    using namespace Entities;

    List<Entity*>::Iterator platformIterator = pEntityList->first();

    while (platformIterator != pEntityList->last()) {
      List<Entity*>::Iterator playerIterator = m_pPlayers->first();
      while (playerIterator != m_pPlayers->last()) {
        checkCollision(*platformIterator, static_cast<Player*>(*playerIterator));
        ++playerIterator;
      }
      ++platformIterator;
    }
  }

  void CollisionManager::exec() {
    verifyCollisionEntities(m_pPlatforms);
    verifyCollisionEntities(m_pEnemies);
  }
}