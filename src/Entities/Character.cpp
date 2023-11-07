/* Main Include */
#include "Entities/Character.h"

namespace Entities {
  Character::Character()
    : Entity(sf::Vector2f(0.f, 0.f))
    , m_healthPoints(0)
    , m_speed(300.f)
    , m_velocity(sf::Vector2f(0.f, 0.f))
  {

  }

  Character::~Character() {

  }

  void Character::setVelocity(const sf::Vector2f velocity) {
    m_velocity = velocity;
  }

  sf::Vector2f Character::getVelocity() const {
    return m_velocity;
  }

  const int Character::getHealthPoints() const {
    return m_healthPoints;
  }

  void Character::move() {
    m_sprite.move(m_velocity);
  }

  void Character::move(const sf::Vector2f movement) {
    m_sprite.move(movement);
  }
}