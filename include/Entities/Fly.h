#ifndef FLY_H
#define FLY_H

/* Program Defined */
#include "Entities/Enemy.h"

namespace Entities {
  class Fly : public Enemy {
    private:
      const float m_range;
      bool m_direction;

    public:
      Fly(sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
      ~Fly();
      virtual void movementPattern();
      virtual void exec();
      virtual void save();
  };
}

#endif