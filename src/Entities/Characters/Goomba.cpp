/* Main Include */
#include "Entities/Characters/Goomba.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Goomba::Goomba(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition)
      : Enemy(5, spawnPosition)
      , m_range(64.f)
      , m_direction(rand() % 2)
    {
      setEntityId(EntityID::GoombaE);
      setTextureID(textureID);
      setTexture(texture);
      setSpeed(50.f);
      setVelocity(sf::Vector2f(m_speed * m_dt, 0.f));
    }

    Goomba::~Goomba() {

    }

    void Goomba::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (m_healthPoints <= 0)
        return;

      checkGrounded(pEntity, type);
      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          playerCollide(dynamic_cast<Player*>(pEntity), type);
          break;
        case EntityTag::ObstacleTag:
          checkNewTerritory(pEntity, type, overlap);
          break;
        case EntityTag::EnemyTag:
          checkNewTerritory(pEntity, type, overlap);
          break;
        default:
          break;
      }
    }

    void Goomba::checkNewTerritory(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (type == Manager::Collision::CollisionType::Horizontal && fabs(overlap) > 0.1f) {
        if (pEntity->getPosition().x > getPosition().x)
          m_spawnPosition = sf::Vector2f(getPosition().x - m_range * 1.1f, getPosition().y);
        else
          m_spawnPosition = sf::Vector2f(getPosition().x + m_range * 1.1f, getPosition().y);
      }
    }

    void Goomba::movementPattern() {
      if (getPosition().x >= (m_spawnPosition.x + m_range))
        m_direction = true;
      else if (getPosition().x <= (m_spawnPosition.x - m_range))
        m_direction = false;
      
      if (m_direction)
        m_velocity.x = -m_speed * m_dt;
      else
        m_velocity.x = m_speed * m_dt;
    }

    void Goomba::save(nlohmann::ordered_json& jsonData) {
      Enemy::save(jsonData);
      jsonData["direction"] = m_direction;
    }

    void Goomba::loadSave(const nlohmann::ordered_json& jsonData) {
      Enemy::loadSave(jsonData);
      m_direction = jsonData["direction"];
    }

    void Goomba::update() {
      if (!m_isMidAir && !m_isStaggered)
        movementPattern();
    }
  }
}