/* Main Include */
#include "Entities/Enemy.h"

/* Program Defined */
#include "Entities/Player.h"

namespace Entities {
  Enemy::Enemy(const sf::Vector2f spawnPosition)
    : Character()
    , m_animation(this)
    , m_attack(1)
    , m_spawnPosition(spawnPosition)
  {
    setEntityId(EntityID::EnemyE);
    setEntityTag(EntityTag::EnemyTag);
    m_sprite.setPosition(spawnPosition);
  }

  Enemy::~Enemy() {

  }

  void Enemy::damagePlayer(Player* pPlayer) {
    pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
  }
}