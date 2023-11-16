/* Main Include */
#include "Manager/Collision/CollisionManager.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/Player.h"

/* Standard Library */
#include <iostream>
#include <algorithm>

namespace Manager {
  namespace Collision {
    Manager::Collision::CollisionStrategyFactory* CollisionManager::m_pCollisionFactory(Manager::Collision::CollisionStrategyFactory::getInstance());

    CollisionManager::CollisionManager()
      : m_pPlayers(NULL)
      , m_pStaticEntities(NULL)
      , m_pDynamicEntities(NULL)
    {
      
    }

    CollisionManager::~CollisionManager() {
      m_pPlayers = NULL;
      m_pStaticEntities = NULL;
      m_pDynamicEntities = NULL;
    }

    void CollisionManager::setPlayersList(EntityList* pPlayersList) {
      if (pPlayersList)
        m_pPlayers = pPlayersList;
    }

    void CollisionManager::setStaticEntities(EntityList* pStaticList) {
      if (pStaticList)
        m_pStaticEntities = pStaticList;
    }

    void CollisionManager::setDynamicEntities(EntityList* pDynamicList) {
      if (pDynamicList)
        m_pDynamicEntities = pDynamicList;
    }

    void CollisionManager::verifyOverlap(std::pair<Entities::Entity*, Entities::Entity*> entities) {
      using namespace Entities;

      const sf::FloatRect cEntityCoordinates = entities.first->getGlobalBounds();
      const sf::FloatRect mEntityCoordinates = entities.second->getGlobalBounds();
      std::unordered_map<int, Entity*> collisionMap = entities.first->getCollisionMap();

      if (mEntityCoordinates.intersects(cEntityCoordinates, m_intersectionRect)) {
        if (collisionMap.count(entities.second->getId()) > 0)
          return;

        float xOverlap = m_intersectionRect.width;
        float yOverlap = m_intersectionRect.height;

        if (yOverlap < xOverlap) {
          if (mEntityCoordinates.top < cEntityCoordinates.top)
            yOverlap *= -1;
          applyCollision(entities, CollisionType::Vertical, yOverlap);
        } else {
          if (mEntityCoordinates.left < cEntityCoordinates.left)
            xOverlap *= -1;
          applyCollision(entities, CollisionType::Horizontal, xOverlap);
        }
      } else {
        collisionMap.erase(entities.second->getId());
        entities.second->getCollisionMap().erase(entities.first->getId());
      }
    }

    void CollisionManager::applyCollision(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionType type, float overlap) {
      entities.first->collide(entities.second, type, overlap);
      entities.second->collide(entities.first, type, overlap);

      entities.first->getCollisionMap().insert(std::make_pair(entities.second->getId(), entities.second));
      entities.second->getCollisionMap().insert(std::make_pair(entities.first->getId(), entities.first));
      
      CollisionStrategy* strategy;
      strategy = entities.first->getCollisionStrategy(entities.second->getEntityTag());
      strategy->collide(entities.first, entities.second, type, overlap);

      strategy = entities.second->getCollisionStrategy(entities.first->getEntityTag());
      strategy->collide(entities.second, entities.first, type, overlap);
    }

    void CollisionManager::verifyCollisions() {
      List<Entities::Entity*>::Iterator staticIterator;
      List<Entities::Entity*>::Iterator dynamicIterator;

      for (dynamicIterator = m_pPlayers->first(); dynamicIterator != m_pPlayers->last(); ++dynamicIterator)
        verifyCollisionStatic(*dynamicIterator);

      for (dynamicIterator = m_pDynamicEntities->first(); dynamicIterator != m_pDynamicEntities->last(); ++dynamicIterator) {
        verifyCollisionDynamic(*dynamicIterator, dynamicIterator + 1);
        verifyCollisionDynamic(*dynamicIterator, m_pPlayers->first());
        verifyCollisionStatic(*dynamicIterator);
      }
    }

    void CollisionManager::verifyCollisionStatic(Entities::Entity* pEntity) {
      List<Entities::Entity*>::Iterator staticIterator;

      for (staticIterator = m_pStaticEntities->first(); staticIterator != m_pStaticEntities->last(); ++staticIterator)
        verifyOverlap(std::make_pair(*staticIterator, pEntity));
    }

    void CollisionManager::verifyCollisionDynamic(Entities::Entity* pEntity, List<Entities::Entity*>::Iterator it) {
      List<Entities::Entity*>::Iterator dynamicIterator;

      for (dynamicIterator = it; dynamicIterator != m_pDynamicEntities->last(); ++dynamicIterator)
        if ((*dynamicIterator)->getMoved() || pEntity->getMoved())
          verifyOverlap(std::make_pair(*dynamicIterator, pEntity));
    }

    CollisionStrategy* CollisionManager::getCollisionStrategy(StrategyId id) {
      return m_pCollisionFactory->getCollisionStrategy(id);
    }
  }
}