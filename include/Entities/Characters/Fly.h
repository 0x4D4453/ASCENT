#ifndef FLY_H
#define FLY_H

/* Program Defined */
#include "Entities/Characters/Enemy.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    class Fly : public Enemy {
      private:
        const float m_timeBetweenFlaps;
        const float m_buoyancy;
        const float m_range;
        float m_timeSinceLastFlap;
      
      private:
        virtual void update();
        void glide();
        void flapWings();
        bool checkDistanceToSpawn();

      public:
        Fly(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
        ~Fly();
        virtual void movementPattern();
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif