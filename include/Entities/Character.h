#ifndef CHARACTER_H
#define CHARACTER_H

/* Program Defined */
#include "Entities/Entity.h"

namespace Entities {
  class Character : public Entity {
    protected:
      int m_healthPoints;
    
    public:
      Character();
      virtual ~Character();
      const int getHealthPoints() const;
      virtual void save() = 0;
      virtual void exec() = 0;
  };
}

#endif