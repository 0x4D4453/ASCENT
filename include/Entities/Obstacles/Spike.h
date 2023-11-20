#ifndef SPIKE_H
#define SPIKE_H

#include "Entities/Obstacles/Obstacle.h"

/* Program Defined */
#include "Entities/Characters/Player.h"

namespace Entities {
  namespace Obstacles {
    class Spike : public Obstacle {
      private:
        const int m_attack;
      
      public:
        Spike(sf::Texture& texture, sf::Vector2f position);
        ~Spike();
        void damagePlayer(Characters::Player* pPlayer);
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save();
        virtual void exec();
    };
  }
}

#endif