#ifndef CHARACTER_H
#define CHARACTER_H

/* Program Defined */
#include "Entities/Entity.h"

namespace Entities {
  namespace Characters {
    class Character : public Entity {
      protected:
        sf::Clock m_collisionClock;
        int m_healthPoints;
      
      public:
        Character();
        virtual ~Character();
        const int getHealthPoints() const;
        void setHealthPoints(const int healthPoints);
        virtual void save() = 0;
        virtual void exec() = 0;
    };
  }
}

#endif