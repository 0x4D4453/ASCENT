#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Program Defined */
#include "Entities/Entity.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  class Projectile : public Entity {
    protected:
      sf::Vector2f m_direction;
    
    public:
      Projectile(
        sf::Vector2f position = sf::Vector2f(0.f, 0.f),
        sf::Vector2f direction = sf::Vector2f(0.f, 0.f),
        const float speed = 0.f
      );
      virtual ~Projectile();
      virtual void setup();
      virtual void save();
      virtual void exec();
  };
};

#endif