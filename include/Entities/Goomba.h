#ifndef GOOMBA_H
#define GOOMBA_H

#include "Entities/Enemy.h"

namespace Entities {
  class Goomba : public Enemy {
    private:
      const float m_range;
      bool m_direction;

    public:
      Goomba(sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
      ~Goomba();
      virtual void movementPattern();
      virtual void exec();
      virtual void save();
  };
}

#endif