/* Main Include */
#include "Entities/Characters/Fly.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Fly::Fly(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition)
      : Enemy(spawnPosition)
      , m_range(32.f)
      , m_direction(rand() % 2)
    {
      setEntityId(EntityID::FlyE);
      setTextureID(textureID);
      setTexture(texture);
      setSpeed(20.f);
      setVelocity(sf::Vector2f(0.f, m_speed * m_dt));
    }

    Fly::~Fly() {

    }

    void Fly::movementPattern() {
      if (getPosition().y >= (m_spawnPosition.y + m_range))
        m_direction = true;
      else if (getPosition().y <= (m_spawnPosition.y - m_range))
        m_direction = false;
      
      if (m_direction)
        m_velocity.y = -m_speed * m_dt;
      else
        m_velocity.y = m_speed * m_dt;
    }

    void Fly::save(nlohmann::ordered_json& jsonData) {
      nlohmann::ordered_json flyData;

      flyData["ID"] = getEntityId();
      flyData["textureID"] = m_textureID;
      flyData["hp"] = getHealthPoints();
      flyData["spawnPosition"] = { {"x", m_spawnPosition.x}, {"y", m_spawnPosition.y} };
      flyData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
      flyData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
      flyData["direction"] = m_direction;

      jsonData.push_back(flyData);
    }

    void Fly::loadSave(const nlohmann::ordered_json& jsonData) {
      m_spawnPosition = sf::Vector2f(jsonData["spawnPosition"]["x"].template get<float>(), jsonData["spawnPosition"]["y"].template get<float>());
      setVelocity(sf::Vector2f(jsonData["velocity"]["x"].template get<float>(), jsonData["velocity"]["y"].template get<float>()));
      m_healthPoints = jsonData["hp"].template get<int>();
      m_direction = jsonData["direction"].template get<bool>();
    }

    void Fly::update() {
      if (!m_isStaggered && m_healthPoints > 0)
        movementPattern();
    }
  }
}