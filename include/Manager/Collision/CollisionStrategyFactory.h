#ifndef COLLISIONSTRATEGYFACTORY_H
#define COLLISIONSTRATEGYFACTORY_H

/* Program Defined */
#include "Manager/Collision/CollisionStrategy.h"

/* Standard Library */
#include <map>

namespace Manager {
  namespace Collision {
    enum class StrategyId {
      Default,
      Platform,
      Player,
      NoCollision,
    };

    class CollisionStrategyFactory {
      private:
        static CollisionStrategyFactory* m_instance;
        std::map<StrategyId, CollisionStrategy*> m_strategyPool;

      private:
        CollisionStrategyFactory();

      public:
        ~CollisionStrategyFactory();
        static CollisionStrategyFactory* getInstance();

        CollisionStrategy* getCollisionStrategy(StrategyId id);
    };
  }
}

#endif