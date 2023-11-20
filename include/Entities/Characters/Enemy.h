#ifndef ENEMY_H
#define ENEMY_H

/* Program Defined */
#include "Entities/Characters/Character.h"

/* Forward Declaration */
namespace Entities { namespace Characters { class Player; } }

namespace Entities {
  namespace Characters {
    class Enemy : public Character {
      protected:
        const int m_attack;
        sf::Vector2f m_spawnPosition;

      public:
        Enemy(const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
        ~Enemy();
        void damagePlayer(Player* pPlayer);
        virtual void movementPattern() = 0;
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
    };
  }
}

#endif