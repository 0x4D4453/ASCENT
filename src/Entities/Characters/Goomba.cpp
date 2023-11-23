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
      : Enemy(spawnPosition)
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
      nlohmann::ordered_json goombaData;

      goombaData["ID"] = getEntityId();
      goombaData["textureID"] = m_textureID;
      goombaData["hp"] = getHealthPoints();
      goombaData["spawnPosition"] = { {"x", m_spawnPosition.x}, {"y", m_spawnPosition.y} };
      goombaData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
      goombaData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
      goombaData["direction"] = m_direction;

      jsonData.push_back(goombaData);
    }

    void Goomba::loadSave(const nlohmann::ordered_json& jsonData) {
      m_spawnPosition = sf::Vector2f(jsonData["spawnPosition"]["x"].template get<float>(), jsonData["spawnPosition"]["y"].template get<float>());
      setVelocity(sf::Vector2f(jsonData["velocity"]["x"], jsonData["velocity"]["y"]));
      m_healthPoints = jsonData["hp"];
      m_direction = jsonData["direction"];
    }

    void Goomba::update() {
      if (!m_isMidAir && !m_isStaggered && m_healthPoints > 0)
        movementPattern();
    }
  }
}