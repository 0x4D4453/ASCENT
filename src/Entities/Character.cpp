/* Main Include */
#include "Entities/Character.h"

namespace Entities {
  Character::Character()
    : Entity(sf::Vector2f(0.f, 0.f))
    , m_healthPoints(3)
  {
    setEntityId(EntityID::CharacterE);
  }

  Character::~Character() {

  }

  const int Character::getHealthPoints() const {
    return m_healthPoints;
  }

  void Character::setHealthPoints(const int healthPoints) {
    m_healthPoints = healthPoints;
  }
}