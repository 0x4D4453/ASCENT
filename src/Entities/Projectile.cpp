/* Main Include */
#include "Entities/Projectile.h"

/* Program Defined */
#include "Utility/Constants.h"
#include "Utility/Textures.h"
#include "Utility/CustomVector.h"

#include <cmath>

namespace Entities {
  Projectile::Projectile(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, const float scale, const float speed, const float angle) 
    : Entity(position, scale, speed)
    , m_maxRange(500.f)
    , m_angle(angle)
    , m_attack(1.f)
    , m_pList(NULL)
    , m_distance(0.f)
  {
    setEntityId(EntityID::ProjectileE);
    setEntityTag(EntityTag::ProjectileTag);
    setEntityType(EntityType::Dynamic);
    setTextureID(textureID);
    setTexture(texture);
    setKnockback(0.5f);
    setVelocity(sf::Vector2f(speed * cos(angle), -speed * sin(angle)));
    setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
  }

  Projectile::~Projectile() {
    m_pList = NULL;
  }

  void Projectile::autoRemove() {
    // if (m_pList)
    //   m_pList->remove(this);
    
    // delete this;
  }

  void Projectile::checkOutOfBounds() {
    CustomVector vector(m_velocity);
    m_distance += vector.getMagnitude();

    if (m_distance >= m_maxRange)
      autoRemove();
  }

  void Projectile::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
    switch (pEntity->getEntityTag()) {
      case EntityTag::PlayerTag:
        playerCollide(dynamic_cast<Characters::Player*>(pEntity), type);
        break;
      case EntityTag::EnemyTag:
        break;
      default:
        autoRemove();
        break;
    }
  }

  void Projectile::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
    if (pPlayer->getIsAttacking()) {
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::NoCollision);
    } else {
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
      damagePlayer(pPlayer);
      autoRemove();
    }
  }

  void Projectile::damagePlayer(Characters::Player* pPlayer) {
    pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
  }

  void Projectile::setList(EntityList* pList) {
    m_pList = pList;
  }

  void Projectile::exec() {
    move();
    checkOutOfBounds();
  }

  void Projectile::save(nlohmann::ordered_json& jsonData) {

  }

  void Projectile::loadSave(const nlohmann::ordered_json& jsonData) {

  }
}