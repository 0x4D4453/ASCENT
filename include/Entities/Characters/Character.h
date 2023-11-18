#ifndef CHARACTER_H
#define CHARACTER_H

/* Program Defined */
#include "Entities/Entity.h"

/* JSON Library */
#include "nlohmann/json.hpp"

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
        virtual void save(nlohmann::ordered_json& jsonData) = 0;
        virtual void loadSave(const nlohmann::ordered_json& jsonData) = 0;
        virtual void exec() = 0;
    };
  }
}

#endif