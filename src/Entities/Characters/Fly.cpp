/* Main Include */
#include "Entities/Characters/Fly.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Animation/EnemyAnimation.h"
#include "Utility/CustomVector.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Fly::Fly(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition)
      : Enemy(10, spawnPosition)
      , m_timeBetweenFlaps(0.2f)
      , m_buoyancy(Constants::GRAVITY * (0.9f + (rand() % 5) / 100.f))
      , m_range(16.f)
      , m_timeSinceLastFlap(0.f)
    {
      setEntityId(EntityID::FlyE);
      setTextureID(textureID);
      setTexture(texture);
      setSpeed(30.f);

      setAnimation(new Animations::EnemyAnimation(this, Animations::MDirection::Y, 0.2f));
    }

    Fly::~Fly() {

    }

    void Fly::glide() {
      m_velocity.y -= m_buoyancy * m_dt;
    }

    void Fly::flapWings() {
      m_velocity.y = -sqrt(2 * m_range * Constants::GRAVITY * m_dt);
    }

    bool Fly::checkDistanceToSpawn() {
      sf::Vector2f position = getPosition();

      if (position.x < m_spawnPosition.x)
        m_velocity.x = m_speed * m_dt;
      else if (position.x > m_spawnPosition.x)
        m_velocity.x = -m_speed * m_dt;

      if (position.y < m_spawnPosition.y)
        return false;

      CustomVector vector({ position.x - m_spawnPosition.x, position.y - m_spawnPosition.y });
      return vector.getMagnitude() > m_range;
    }

    void Fly::movementPattern() {
      m_timeSinceLastFlap += m_dt;
      if (m_timeSinceLastFlap >= m_timeBetweenFlaps && checkDistanceToSpawn()) {
        m_timeSinceLastFlap = 0.f;
        flapWings();
      } else {
        glide();
      }
    }

    void Fly::save(nlohmann::ordered_json& jsonData) {
      Enemy::save(jsonData);
    }

    void Fly::loadSave(const nlohmann::ordered_json& jsonData) {
      Enemy::loadSave(jsonData);
    }

    void Fly::update() {
      if (m_isStaggered)
        glide();
      else
        movementPattern();
    }
  }
}