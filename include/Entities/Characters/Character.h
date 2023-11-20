#ifndef CHARACTER_H
#define CHARACTER_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Animation/Animation.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    class Character : public Entity {
      protected:
        Animations::Animation* m_animation;
        sf::Clock m_collisionClock;
        const int m_maxHealthPoints;
        int m_healthPoints;
      
      protected:
        virtual void update() = 0;
        void recoverColor();
      
      public:
        Character();
        virtual ~Character();
        const int getMaxHealthPoints() const;
        const int getHealthPoints() const;
        void setHealthPoints(const int healthPoints);
        virtual void save(nlohmann::ordered_json& jsonData) = 0;
        virtual void loadSave(const nlohmann::ordered_json& jsonData) = 0;
        virtual void exec();
    };
  }
}

#endif