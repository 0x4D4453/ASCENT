/* Main Include */
#include "Entities/Characters/Character.h"

namespace Entities {
  namespace Characters {
    Character::Character()
      : Entity(sf::Vector2f(0.f, 0.f))
      , m_collisionClock()
      , m_healthPoints(3)
    {
      setEntityId(EntityID::CharacterE);
      setEntityType(EntityType::Dynamic);
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
}