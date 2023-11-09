#ifndef ENEMY_H
#define ENEMY_H

/* Program Defined */
#include "Entities/Character.h"

/* Forward Declaration */
namespace Entities { class Player; }

namespace Entities {
  class Enemy : public Character {
    protected:
      const int m_attack;
      sf::Vector2f m_spawnPosition;

    public:
      Enemy(const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f));
      ~Enemy();
      void damagePlayer(Player* pPlayer);
      virtual void movementPattern() = 0;
  };
}

#endif