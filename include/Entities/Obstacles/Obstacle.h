#ifndef OBSTACLE_H
#define OBSTACLE_H

/* Program Defined */
#include "Entities/Entity.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  namespace Obstacles {
    class Obstacle : public Entity {
      protected:
        const bool m_harmful;

      public:
        Obstacle(sf::Vector2f position = sf::Vector2f(0.f, 0.f), const bool harmful = false);
        virtual ~Obstacle();
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) = 0;
        virtual void save() = 0;
        virtual void exec() = 0;
    };
  }
}

#endif