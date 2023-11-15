/* Main Include */
#include "Manager/Collision/CollisionStrategyFactory.h"

/* Program defined */
#include "Manager/Collision/NoCollision.h"
#include "Manager/Collision/DefaultCollision.h"
#include "Manager/Collision/KnockbackCollision.h"

namespace Manager {
  namespace Collision {
    CollisionStrategyFactory* CollisionStrategyFactory::m_instance(NULL);

    CollisionStrategyFactory::CollisionStrategyFactory()
      : m_strategyPool()
    {

    }

    CollisionStrategyFactory::~CollisionStrategyFactory() {
      std::map<StrategyId, CollisionStrategy*>::iterator it = m_strategyPool.begin();

      while (it != m_strategyPool.end()) {
        delete (*it).second;
        m_strategyPool.erase((*it).first);
        it++;
      }
    }

    CollisionStrategyFactory* CollisionStrategyFactory::getInstance() {
      if (!m_instance)
        m_instance = new CollisionStrategyFactory();
      return m_instance;
    }

    CollisionStrategy* CollisionStrategyFactory::getCollisionStrategy(StrategyId id) {
      if (m_strategyPool[id])
        return m_strategyPool[id];
      
      CollisionStrategy* strategy = NULL;
      switch (id) {
        case StrategyId::NoCollision:
          strategy = new NoCollision();
          break;
        case StrategyId::Default:
          strategy = new DefaultCollision();
          break;
        case StrategyId::KnockbackCollision:
          strategy = new KnockbackCollision();
          break;
        default:
          strategy = new NoCollision();
          break;
      }

      return strategy;
    }
  }
}