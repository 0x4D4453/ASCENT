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

  /* DO NOT use intersects from SFML */
  void CollisionManager::verifyOverlap(Entities::Entity* entity) {
    using namespace Entities;

    Entity::Coordinates cEntityCoordinates = entity->getCoordinates();
    Entity::Coordinates mEntityCoordinates = m_pEntity->getCoordinates();

    float xOverlap = std::max(0.f, std::min(mEntityCoordinates.right, cEntityCoordinates.right) 
                    - std::max(mEntityCoordinates.left, cEntityCoordinates.left));
    float yOverlap = std::max(0.f, std::min(mEntityCoordinates.bottom, cEntityCoordinates.bottom) 
                    - std::max(mEntityCoordinates.top, cEntityCoordinates.top));

    if (yOverlap != 0 && yOverlap < xOverlap) {
      if (mEntityCoordinates.top < cEntityCoordinates.top)
        yOverlap *= -1;
      entity->collide(m_pEntity, CollisionType::Vertical, yOverlap);
      m_pEntity->collide(entity, CollisionType::Vertical, yOverlap);
    } else if (xOverlap != 0 && xOverlap < yOverlap) {
      if (mEntityCoordinates.left < cEntityCoordinates.left)
        xOverlap *= -1;
      entity->collide(m_pEntity, CollisionType::Horizontal, xOverlap);
      m_pEntity->collide(entity, CollisionType::Horizontal, xOverlap);
    }
  }

  void CollisionManager::verifyCollision(Entities::Entity* entity) {
    m_pEntity = entity;
    verifyCollisionObstacles();
  }

  void CollisionManager::verifyCollisionObstacles() {
    List<Entities::Entity*>::Iterator obstaclesIterator;

    for (obstaclesIterator = m_pObstacles->first(); obstaclesIterator != m_pObstacles->last(); ++obstaclesIterator)
      verifyOverlap(*obstaclesIterator);
  }
}