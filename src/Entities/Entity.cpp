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

  Entity::Coordinates::Coordinates(float l, float r, float t, float b) 
    : left(l), right(r), top(t), bottom(b)
  {

  }

  Entity::Coordinates::~Coordinates() {

  }

  void Entity::setPosition(sf::Vector2f position) {
    m_position = position;
    m_sprite.setPosition(m_position);
  }

  sf::Vector2f Entity::getPosition() const {
    return m_sprite.getPosition();
  }

  Entity::Coordinates Entity::getCoordinates() const {
    sf::FloatRect entityBounds = getGlobalBounds();
    float entityLeft = entityBounds.left;
    float entityRight = entityBounds.left + entityBounds.width;
    float entityTop = entityBounds.top;
    float entityBottom = entityBounds.top + entityBounds.width;

    return Entity::Coordinates(entityLeft, entityRight, entityTop, entityBottom);
  }
}