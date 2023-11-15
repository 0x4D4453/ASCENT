/* Main Include */
#include "Manager/Collision/CollisionManager.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"

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

    bool CollisionManager::verifyOverlap(std::pair<Entities::Entity*, Entities::Entity*> entities) {
      using namespace Entities;

      const sf::FloatRect cEntityCoordinates = entities.first->getGlobalBounds();
      const sf::FloatRect mEntityCoordinates = entities.second->getGlobalBounds();
      bool overlap = mEntityCoordinates.intersects(cEntityCoordinates, m_intersectionRect);

      if (overlap) {
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
      }

      return overlap;
    }

    void CollisionManager::applyCollision(std::pair<Entities::Entity*, Entities::Entity*> entities, CollisionType type, float overlap) {
      entities.first->collide(entities.second, type, overlap);
      entities.second->collide(entities.first, type, overlap);
      
      CollisionStrategy* strategy;
      strategy = entities.first->getCollisionStrategy(entities.second->getEntityTag());
      strategy->collide(entities.first, entities.second, type, overlap);

      strategy = entities.second->getCollisionStrategy(entities.first->getEntityTag());
      strategy->collide(entities.second, entities.first, type, overlap);
    }

    void CollisionManager::verifyCollisions() {
      List<Entities::Entity*>::Iterator staticIterator;
      List<Entities::Entity*>::Iterator dynamicIterator;

      for (dynamicIterator = m_players->first(); dynamicIterator != m_players->last(); ++dynamicIterator)
        verifyCollisionStatic(*dynamicIterator);

      for (dynamicIterator = m_dynamicEntities->first(); dynamicIterator != m_dynamicEntities->last(); ++dynamicIterator) {
        verifyCollisionDynamic(*dynamicIterator, dynamicIterator + 1);
        verifyCollisionDynamic(*dynamicIterator, m_players->first());
        verifyCollisionStatic(*dynamicIterator);
      }
    }

    void CollisionManager::verifyCollisionStatic(Entities::Entity* entity) {
      List<Entities::Entity*>::Iterator staticIterator;
      bool overlap = false;

      for (staticIterator = m_staticEntities->first(); staticIterator != m_staticEntities->last(); ++staticIterator)
        overlap = verifyOverlap(std::make_pair(*staticIterator, entity)) || overlap;

      entity->setIsColliding(overlap);
    }

    void CollisionManager::verifyCollisionDynamic(Entities::Entity* entity, List<Entities::Entity*>::Iterator it) {
      List<Entities::Entity*>::Iterator dynamicIterator;
      bool overlap = false;

      for (dynamicIterator = it; dynamicIterator != m_dynamicEntities->last(); ++dynamicIterator)
        if ((*dynamicIterator)->getMoved() || entity->getMoved())
          overlap = verifyOverlap(std::make_pair(*dynamicIterator, entity)) || overlap;

      entity->setIsColliding(overlap);
    }

    CollisionStrategy* CollisionManager::getCollisionStrategy(StrategyId id) {
      return m_pCollisionFactory->getCollisionStrategy(id);
    }
  }
}