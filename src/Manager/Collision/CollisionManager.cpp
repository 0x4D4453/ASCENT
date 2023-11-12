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

    void CollisionManager::verifyOverlap(Entities::Entity* entity) {
      using namespace Entities;

      const sf::FloatRect cEntityCoordinates = entity->getGlobalBounds();
      const sf::FloatRect mEntityCoordinates = m_pEntity->getGlobalBounds();

      if (mEntityCoordinates.intersects(cEntityCoordinates, m_intersectionRect)) {
        float xOverlap = m_intersectionRect.width;
        float yOverlap = m_intersectionRect.height;

        if (yOverlap != 0 && yOverlap < xOverlap) {
          if (mEntityCoordinates.top < cEntityCoordinates.top)
            yOverlap *= -1;
          entity->collide(m_pEntity, Manager::Collision::CollisionType::Vertical, yOverlap);
          m_pEntity->collide(entity, Manager::Collision::CollisionType::Vertical, yOverlap);
        } else if (xOverlap != 0 && xOverlap < yOverlap) {
          if (mEntityCoordinates.left < cEntityCoordinates.left)
            xOverlap *= -1;
          entity->collide(m_pEntity, Manager::Collision::CollisionType::Horizontal, xOverlap);
          m_pEntity->collide(entity, Manager::Collision::CollisionType::Horizontal, xOverlap);
        }
      }
    }

    void CollisionManager::verifyCollision(Entities::Entity* entity) {
      m_pEntity = entity;
      verifyCollisionObstacles();
      verifyCollisionEnemies();
    }

    void CollisionManager::verifyCollisionObstacles() {
      List<Entities::Entity*>::Iterator obstaclesIterator;

      for (obstaclesIterator = m_pObstacles->first(); obstaclesIterator != m_pObstacles->last(); ++obstaclesIterator)
        verifyOverlap(*obstaclesIterator);
    }

    void CollisionManager::verifyCollisionEnemies() {
      List<Entities::Entity*>::Iterator enemiesIterator;

      for (enemiesIterator = m_pEnemies->first(); enemiesIterator != m_pEnemies->last(); ++enemiesIterator)
        verifyOverlap(*enemiesIterator);
    }

    CollisionStrategy* CollisionManager::getCollisionStrategy(StrategyId id) {
      return m_pCollisionFactory->getCollisionStrategy(id);
    }
  }
}