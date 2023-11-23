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
        Spike(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~Spike();
        void damagePlayer(Characters::Player* pPlayer);
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save();
        virtual void exec();
    };
  }
}

#endif