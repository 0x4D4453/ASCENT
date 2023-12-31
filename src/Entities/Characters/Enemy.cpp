/* Main Include */
#include "Entities/Characters/Enemy.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Animation/EnemyAnimation.h"

namespace Entities {
  namespace Characters {
    Enemy::Enemy(const int bounty, const sf::Vector2f spawnPosition, const float scale, const int maxHealth)
      : Character(scale, maxHealth)
      , m_attack(1)
      , m_spawnPosition(spawnPosition)
      , m_bounty(bounty)
    {
      setEntityId(EntityID::EnemyE);
      setEntityTag(EntityTag::EnemyTag);
      m_sprite.setPosition(spawnPosition);

      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
      setAnimation(new Animations::EnemyAnimation(this, Animations::MDirection::X, 0.2f));
    }

    Enemy::~Enemy() {

    }

    void Enemy::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
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
      if (pPlayer->getIsAttacking() || pPlayer->getIsImmune()) {
        setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::PhaseCollision);
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

    const int Enemy::getBounty() const {
      return m_bounty;
    }

    void Enemy::save(nlohmann::ordered_json& jsonData) {
      Character::save(jsonData);
      jsonData["spawnPosition"] = { {"x", m_spawnPosition.x}, {"y", m_spawnPosition.y} };
    }

    void Enemy::loadSave(const nlohmann::ordered_json& jsonData) {
      Character::loadSave(jsonData);
      m_spawnPosition = sf::Vector2f(jsonData["spawnPosition"]["x"].template get<float>(), jsonData["spawnPosition"]["y"].template get<float>());
    }
  }
}