/* Main Include */
#include "Manager/Collision/CollisionManager.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"
#include "Utility/List.h"

/* Standard Library */
#include <iostream>
#include <algorithm>

namespace Manager {
  namespace Collision {
    Manager::Collision::CollisionStrategyFactory* CollisionManager::m_pCollisionFactory(Manager::Collision::CollisionStrategyFactory::getInstance());

    CollisionManager::CollisionManager()
      : m_pEntity(NULL)
      , m_pPlayers(NULL)
      , m_pObstacles(NULL)
      , m_pEnemies(NULL)
    {

    }

    CollisionManager::~CollisionManager() {
      m_pEntity = NULL;
      m_pPlayers = NULL;
      m_pObstacles = NULL;
      m_pEnemies = NULL;
    }

    void CollisionManager::setPlayersList(EntityList* playersList) {
      if (playersList)
        m_pPlayers = playersList;
    }

    void CollisionManager::setObstaclesList(EntityList* obstaclesList) {
      if (obstaclesList)
        m_pObstacles = obstaclesList;
    }

    void CollisionManager::setEnemiesList(EntityList* enemiesList) {
      if (enemiesList)
        m_pEnemies = enemiesList;
    }

    bool CollisionManager::verifyOverlap(Entities::Entity* entity) {
      using namespace Entities;

      const sf::FloatRect cEntityCoordinates = entity->getGlobalBounds();
      const sf::FloatRect mEntityCoordinates = m_pEntity->getGlobalBounds();
      bool overlap = false;

      if (mEntityCoordinates.intersects(cEntityCoordinates, m_intersectionRect)) {
        float xOverlap = m_intersectionRect.width;
        float yOverlap = m_intersectionRect.height;
        overlap = true;

        if (yOverlap < xOverlap) {
          if (mEntityCoordinates.top < cEntityCoordinates.top)
            yOverlap *= -1;
          entity->collide(m_pEntity, Manager::Collision::CollisionType::Vertical, yOverlap);
          m_pEntity->collide(entity, Manager::Collision::CollisionType::Vertical, yOverlap);
        } else {
          if (mEntityCoordinates.left < cEntityCoordinates.left)
            xOverlap *= -1;
          entity->collide(m_pEntity, Manager::Collision::CollisionType::Horizontal, xOverlap);
          m_pEntity->collide(entity, Manager::Collision::CollisionType::Horizontal, xOverlap);
        }
      }

      return overlap;
    }

    bool CollisionManager::verifyCollision(Entities::Entity* entity) {
      m_pEntity = entity;
      return verifyCollisionObstacles() || verifyCollisionEnemies();
    }

    bool CollisionManager::verifyCollisionObstacles() {
      List<Entities::Entity*>::Iterator obstaclesIterator;
      bool overlap = false;

      for (obstaclesIterator = m_pObstacles->first(); obstaclesIterator != m_pObstacles->last(); ++obstaclesIterator)
        overlap = verifyOverlap(*obstaclesIterator) || overlap;

      return overlap;
    }

    bool CollisionManager::verifyCollisionEnemies() {
      List<Entities::Entity*>::Iterator enemiesIterator;
      bool overlap = false;

      for (enemiesIterator = m_pEnemies->first(); enemiesIterator != m_pEnemies->last(); ++enemiesIterator)
        overlap = verifyOverlap(*enemiesIterator) || overlap;

      return overlap;
    }

    CollisionStrategy* CollisionManager::getCollisionStrategy(StrategyId id) {
      return m_pCollisionFactory->getCollisionStrategy(id);
    }
  }
}