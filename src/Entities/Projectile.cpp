/* Main Include */
#include "Entities/Projectile.h"

/* Program Defined */
#include "Stage/Stage.h"
#include "Utility/Constants.h"
#include "Utility/Textures.h"
#include "Utility/CustomVector.h"

#include <cmath>

namespace Entities {
  Projectile::Projectile(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, const float scale, const float speed, const float angle) 
    : Entity(position, scale, speed)
    , m_timeLimit(5.f)
    , m_maxRange(500.f)
    , m_angle(angle)
    , m_attack(1.f)
    , m_pStage(NULL)
    , m_distance(0.f)
    , m_timeElapsed(0.f)
    , m_waitingDeletion(false)
  {
    setEntityId(EntityID::ProjectileE);
    setEntityTag(EntityTag::ProjectileTag);
    setEntityType(EntityType::Dynamic);
    setTextureID(textureID);
    setTexture(texture);
    setKnockback(0.5f);
    setVelocity(sf::Vector2f(speed * cos(angle), -speed * sin(angle)));
    setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
    m_sprite.setHitbox({ 4.f, 4.f, 8.f, 8.f });
  }

  Projectile::~Projectile() {
    m_pStage = NULL;
  }

  void Projectile::autoRemove() {
    if (!m_waitingDeletion)
      m_pStage->addToDeletionList(static_cast<Entity*>(this));

    m_waitingDeletion = true;
  }

  void Projectile::checkOutOfBounds() {
    CustomVector vector(m_velocity);
    m_distance += vector.getMagnitude() * m_dt;

    if (m_distance >= m_maxRange)
      autoRemove();
  }

  void Projectile::checkTimeLimit() {
    m_timeElapsed += m_dt;
    if (m_timeElapsed >= m_timeLimit)
      autoRemove();
  }

  void Projectile::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
    switch (pEntity->getEntityTag()) {
      case EntityTag::PlayerTag:
        playerCollide(dynamic_cast<Characters::Player*>(pEntity), type);
        break;
      case EntityTag::EnemyTag:
        break;
      // case EntityTag::ObstacleTag:
      //   autoRemove();
        break;
      default:
        break;
    }
  }

  void Projectile::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
    if (pPlayer->getIsAttacking()) {
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::PhaseCollision);
    } else {
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
      damagePlayer(pPlayer);
      autoRemove();
    }
  }

  void Projectile::damagePlayer(Characters::Player* pPlayer) {
    pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
  }

  void Projectile::setStage(Stages::Stage* pStage) {
    m_pStage = pStage;
  }

  void Projectile::exec() {
    move();
    checkOutOfBounds();
    checkTimeLimit();
  }

  void Projectile::save(nlohmann::ordered_json& jsonData) {

  }

  void Projectile::loadSave(const nlohmann::ordered_json& jsonData) {

  }
}