/* Main Include */
#include "Entities/Goomba.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  Goomba::Goomba(const char* texture, const sf::Vector2f spawnPosition)
    : Enemy(spawnPosition)
    , m_range(32.f)
    , m_direction(rand() % 2)
  {
    setTexture(texture);
    setSpeed(50.f);
  }

  Goomba::~Goomba() {

  }

  void Goomba::movementPattern() {
    if (getPosition().x >= (m_spawnPosition.x + m_range))
      m_direction = true;
    else if (getPosition().x <= (m_spawnPosition.x - m_range))
      m_direction = false;
    
    if (m_direction)
      move(sf::Vector2f(-m_speed * m_dt, 0.f));
    else 
      move(sf::Vector2f(m_speed * m_dt, 0.f));
  }

  void Goomba::save() {

  }

  void Goomba::exec() {
    movementPattern();
  }
}