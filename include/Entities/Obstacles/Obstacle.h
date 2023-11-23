#ifndef OBSTACLE_H
#define OBSTACLE_H

/* Program Defined */
#include "Entities/Entity.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Obstacles {
    class Obstacle : public Entity {
      protected:
        const bool m_harmful;

      public:
        Obstacle(sf::Vector2f position = sf::Vector2f(0.f, 0.f), const bool harmful = false);
        virtual ~Obstacle();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) = 0;
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
        virtual void exec() = 0;
    };
  }
}

#endif