/* Main Include */
#include "Entities/Fly.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  Fly::Fly(sf::Texture& texture, const sf::Vector2f spawnPosition)
    : Enemy(spawnPosition)
    , m_range(32.f)
    , m_direction(rand() % 2)
  {
    setEntityId(EntityID::FlyE);
    setTexture(texture);
    setSpeed(20.f);
  }

  Fly::~Fly() {

  }

  void Fly::movementPattern() {
    sf::Vector2f velocity = sf::Vector2f(0.f, m_speed * m_dt);

    if (getPosition().y >= (m_spawnPosition.y + m_range))
      m_direction = true;
    else if (getPosition().y <= (m_spawnPosition.y - m_range))
      m_direction = false;
    
    if (m_direction)
      velocity.y = -m_speed * m_dt;
    else
      velocity.y = m_speed * m_dt;

    m_animation.update(m_dt, this, velocity);
    move(velocity);
  }

  void Fly::save() {

  }

  void Fly::exec() {
    if (m_healthPoints > 0)
      movementPattern();
    else
      m_animation.update(m_dt, this, sf::Vector2f(0.f, 0.f));
  }
}