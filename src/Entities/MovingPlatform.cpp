/* Main Include */
#include "Entities/MovingPlatform.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  MovingPlatform::MovingPlatform(sf::Texture& texture, sf::Vector2f position)
    : Obstacle(position)
    , m_spawnPosition(position)
    , m_range(64.f)
    , m_direction(true)
  {
    setEntityId(EntityID::MovingPlatformE);
    setEntityGroup(EntityGroup::Static);
    setTexture(texture);
    setSpeed(50.f);
    setVelocity(sf::Vector2f(m_speed * m_dt, 0.f));

    m_pCollision = m_pCollisionManager->getCollisionStrategy(Manager::Collision::StrategyId::Platform);
  }

  MovingPlatform::~MovingPlatform() {

  }

  void MovingPlatform::movementPattern() {
    if (getPosition().x >= (m_spawnPosition.x + m_range))
      m_direction = true;
    else if (getPosition().x <= (m_spawnPosition.x - m_range))
      m_direction = false;
    
    if (m_direction)
      m_velocity.x = -m_speed * m_dt;
    else
      m_velocity.x = m_speed * m_dt;
    
    move();
  }

  void MovingPlatform::save() {

  }

  void MovingPlatform::exec() {
    movementPattern();
  }
}