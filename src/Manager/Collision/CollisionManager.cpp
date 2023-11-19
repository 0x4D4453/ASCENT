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

      const sf::FloatRect firstCoordinates = entities.first->getGlobalBounds();
      const sf::FloatRect secondCoordinates = entities.second->getGlobalBounds();

      if (secondCoordinates.intersects(firstCoordinates, m_intersectionRect)) {
        CollisionInfo info;

        float xOverlap = m_intersectionRect.width;
        float yOverlap = m_intersectionRect.height;

        if (yOverlap < xOverlap) {
          if (secondCoordinates.top < firstCoordinates.top)
            yOverlap *= -1;
          info.type = CollisionType::Vertical;
          info.overlap = yOverlap;
        } else {
          if (secondCoordinates.left < firstCoordinates.left)
            xOverlap *= -1;
          info.type = CollisionType::Horizontal;
          info.overlap = xOverlap;
        }

        if (entities.first->getCurrentCollisions()->count(entities.second->getId()) == 0)
          applyCollision(entities, &info);

        applyCollisionReaction(entities, &info);
      } else {
        entities.first->getCurrentCollisions()->erase(entities.second->getId());
        entities.second->getCurrentCollisions()->erase(entities.first->getId());
      }
    }

    void CollisionManager::applyCollision(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionInfo* info) {
      entities.first->collide(entities.second, info->type, info->overlap);
      entities.second->collide(entities.first, info->type, info->overlap * -1);

      entities.first->getCurrentCollisions()->insert(entities.second->getId());
      entities.second->getCurrentCollisions()->insert(entities.first->getId());
    }

    void CollisionManager::applyCollisionReaction(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionInfo* info) {
      CollisionStrategy* strategy;
      strategy = entities.first->getCollisionStrategy(entities.second->getEntityTag());
      strategy->collide(entities.first, entities.second, info->type, info->overlap);

      strategy = entities.second->getCollisionStrategy(entities.first->getEntityTag());
      strategy->collide(entities.second, entities.first, info->type, info->overlap * -1);
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