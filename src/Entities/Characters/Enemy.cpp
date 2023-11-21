/* Main Include */
#include "Entities/Characters/Enemy.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Animation/EnemyAnimation.h"

namespace Entities {
  namespace Characters {
    Enemy::Enemy(const sf::Vector2f spawnPosition, const float scale, const int maxHealth)
      : Character(scale, maxHealth)
      , m_attack(1)
      , m_spawnPosition(spawnPosition)
    {
      setEntityId(EntityID::EnemyE);
      setEntityTag(EntityTag::EnemyTag);
      m_sprite.setPosition(spawnPosition);

      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
      setAnimation(new Animations::EnemyAnimation(this));
    }

    Enemy::~Enemy() {

    }

    void Enemy::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (m_healthPoints <= 0)
        return;

      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          playerCollide(dynamic_cast<Player*>(pEntity), type);
          break;
        default:
          checkGrounded(pEntity, type);
          break;
      }
    }

    void Enemy::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
      if (pPlayer->getIsAttacking()) {
        setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::NoCollision);
      } else {
        if (m_collisionClock.restart().asSeconds() < getCollisionStrategy(EntityTag::PlayerTag)->getDelay())
          return;

        setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
        damagePlayer(pPlayer);
      }
    }

    void Enemy::damagePlayer(Player* pPlayer) {
      pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
    }
  }
}