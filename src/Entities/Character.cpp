/* Main Include */
#include "Entities/Character.h"

namespace Entities {
  Character::Character()
    : Entity(sf::Vector2f(0.f, 0.f))
    , m_healthPoints(0)
  {
    setEntityId(EntityID::CharacterE);
    setEntityGroup(EntityGroup::Dynamic);
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