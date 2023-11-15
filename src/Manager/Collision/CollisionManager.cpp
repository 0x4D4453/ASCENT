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
      : m_players(NULL)
      , m_staticEntities(NULL)
      , m_dynamicEntities(NULL)
    {
      
    }

    CollisionManager::~CollisionManager() {
      m_players = NULL;
      m_staticEntities = NULL;
      m_dynamicEntities = NULL;
    }

    void CollisionManager::setPlayersList(EntityList* playersList) {
      if (playersList)
        m_players = playersList;
    }

    void CollisionManager::setStaticEntities(EntityList* staticList) {
      if (staticList)
        m_staticEntities = staticList;
    }

    void CollisionManager::setDynamicEntities(EntityList* dynamicList) {
      if (dynamicList)
        m_dynamicEntities = dynamicList;
    }

    bool CollisionManager::verifyOverlap(Entities::Entity* entity1, Entities::Entity* entity2) {
      if (entity1 == entity2)
        return false;

      using namespace Entities;

      const sf::FloatRect cEntityCoordinates = entity1->getGlobalBounds();
      const sf::FloatRect mEntityCoordinates = entity2->getGlobalBounds();
      bool overlap = mEntityCoordinates.intersects(cEntityCoordinates, m_intersectionRect);

      if (overlap) {
        float xOverlap = m_intersectionRect.width;
        float yOverlap = m_intersectionRect.height;

        if (yOverlap < xOverlap) {
          if (mEntityCoordinates.top < cEntityCoordinates.top)
            yOverlap *= -1;
          applyCollision(entity1, entity2, CollisionType::Vertical, yOverlap);
        } else {
          if (mEntityCoordinates.left < cEntityCoordinates.left)
            xOverlap *= -1;
          applyCollision(entity1, entity2, CollisionType::Horizontal, xOverlap);
        }
      }

      return overlap;
    }

    void CollisionManager::applyCollision(Entities::Entity* entity1, Entities::Entity* entity2, CollisionType type, float overlap) {
      CollisionStrategy* strategy;

      strategy = entity1->getCollisionStrategy(entity2->getEntityTag());
      strategy->collide(entity1, entity2, type, overlap);

      strategy = entity2->getCollisionStrategy(entity1->getEntityTag());
      strategy->collide(entity2, entity1, type, overlap);
    }

    void CollisionManager::verifyCollisionStatic() {
      List<Entities::Entity*>::Iterator staticIterator;
      List<Entities::Entity*>::Iterator dynamicIterator;
      bool overlap = false;

      for (dynamicIterator = m_dynamicEntities->first(); dynamicIterator != m_dynamicEntities->last(); ++dynamicIterator)
        verifyCollisionStatic(*dynamicIterator);

      for (dynamicIterator = m_players->first(); dynamicIterator != m_players->last(); ++dynamicIterator)
        verifyCollisionStatic(*dynamicIterator);
    }

    void CollisionManager::verifyCollisionStatic(Entities::Entity* entity) {
      List<Entities::Entity*>::Iterator staticIterator;
      bool overlap = false;

      for (staticIterator = m_staticEntities->first(); staticIterator != m_staticEntities->last(); ++staticIterator)
        overlap = verifyOverlap(*staticIterator, entity) || overlap;

      entity->setIsColliding(overlap);
    }

    void CollisionManager::verifyCollisionDynamic(Entities::Entity* entity) {
      List<Entities::Entity*>::Iterator dynamicIterator;
      bool overlap = false;

      for (dynamicIterator = m_dynamicEntities->first(); dynamicIterator != m_dynamicEntities->last(); ++dynamicIterator)
        overlap = verifyOverlap(entity, *dynamicIterator) || overlap;

      entity->setIsColliding(overlap);
    }

    CollisionStrategy* CollisionManager::getCollisionStrategy(StrategyId id) {
      return m_pCollisionFactory->getCollisionStrategy(id);
    }
  }
}