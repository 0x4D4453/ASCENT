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

    setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
  }

  Enemy::~Enemy() {

  }

  void Enemy::collide(Entity *entity, Manager::Collision::CollisionType type, float overlap) {
    if (entity->getEntityId() != EntityID::PlayerE || m_healthPoints < 1)
      return;

    Player* player = dynamic_cast<Player*>(entity);
    if (player->isAttacking()) {
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::NoCollision);
    } else {
      if (m_collisionClock.restart().asSeconds() < getCollisionStrategy(EntityTag::PlayerTag)->getDelay())
        return;

      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
      damagePlayer(player);
    }
  }

  void Enemy::damagePlayer(Player* pPlayer) {
    pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
  }
}