#ifndef GOOMBA_H
#define GOOMBA_H

/* Program Defined */
#include "Entities/Characters/Enemy.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    class Goomba : public Enemy {
      private:
        const float m_range;
        bool m_direction;
      
      private:
        virtual void update();

      public:
        Goomba(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
        ~Goomba();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void movementPattern();
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif