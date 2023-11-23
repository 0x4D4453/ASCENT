#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"

/* Forward Declaration */
#include "Entities/Characters/Player.h"

namespace Entities {
  namespace Obstacles {
    class MovingPlatform : public Obstacle {
      private:
        sf::Vector2f m_spawnPosition;
        const float m_range;
        bool m_direction;
      
      private:
        void movementPattern();
        void playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type);

      public:
        MovingPlatform(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~MovingPlatform();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void exec();
    };
  }
}

#endif 