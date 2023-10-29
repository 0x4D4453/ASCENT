/* Main Include */
#include "Entities/Entity.h"

namespace Entities {
  Entity::Entity(sf::Vector2f position)
    : Being()
    , m_position(position)
  {
    setPosition(m_position);
  }

  Entity::~Entity() {

  }

  void Entity::setPosition(sf::Vector2f position) {
    m_position = position;
    m_sprite.setPosition(m_position);
  }

  sf::Vector2f Entity::getPosition() const {
    return m_sprite.getPosition();
  }
}