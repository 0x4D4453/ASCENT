/* Main Include */
#include "Entities/Character.h"

namespace Entities {
  float Character::m_dt(0.f);

  Character::Character()
    : Entity(sf::Vector2f(0.f, 0.f))
    , m_healthPoints(0)
    , m_speed(300.f)
    , m_velocity(sf::Vector2f(0.f, 0.f))
  {

  }

  Character::~Character() {

  }

  void Character::setDeltaTime(float dt) {
    m_dt = dt;
  }

  void Character::setVelocity(const sf::Vector2f velocity) {
    m_velocity = velocity;
  }

  void Character::move() {
    m_sprite.move(m_velocity);
  }

  void Character::move(const sf::Vector2f movement) {
    m_sprite.move(movement);
  }
}