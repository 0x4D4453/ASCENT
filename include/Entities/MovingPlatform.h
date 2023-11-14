#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

/* Program Defined */
#include "Entities/Obstacle.h"

namespace Entities {
  class MovingPlatform : public Obstacle {
    private:
      sf::Vector2f m_spawnPosition;
      const float m_range;
      bool m_direction;
    
    private:
      void movementPattern();

    public:
      MovingPlatform(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
      ~MovingPlatform();
      virtual void save();
      virtual void exec();
  };
}

#endif 