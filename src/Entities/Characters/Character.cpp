/* Main Include */
#include "Entities/Characters/Character.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  namespace Characters {
    Character::Character()
      : Entity(sf::Vector2f(0.f, 0.f))
      , m_animation(NULL)
      , m_collisionClock()
      , m_maxHealthPoints(3)
    {
      setEntityId(EntityID::CharacterE);
      setEntityType(EntityType::Dynamic);

      m_healthPoints = m_maxHealthPoints;
    }

    Character::~Character() {
      if (m_animation)
        delete m_animation;

      m_animation = NULL;
    }

    void Character::recoverColor() {
      sf::Color color = m_sprite.getColor();

      if (color.a < 255)
        color += sf::Color(1000.f * m_dt, 0, 0);

      if (color.g < 255)
        color += sf::Color(0, 1000.f * m_dt, 0);

      if (color.b < 255)
        color += sf::Color(0, 0, 1000.f * m_dt);

      m_sprite.setColor(color);
    }

    const int Character::getMaxHealthPoints() const {
      return m_maxHealthPoints;
    }

    const int Character::getHealthPoints() const {
      return m_healthPoints;
    }

    void Character::setHealthPoints(const int healthPoints) {
      if (healthPoints < m_healthPoints)
        m_sprite.setColor(sf::Color::Red);

      m_healthPoints = healthPoints;
    }

    void Character::exec() {
      recoverColor();
      update();

      if (m_animation)
        m_animation->update(m_dt);

      if (m_velocity.x < 0)
        m_sprite.setScale(-m_scale, m_scale);
      else if (m_velocity.x > 0)
        m_sprite.setScale(m_scale, m_scale);

      move();
    }
  }
}