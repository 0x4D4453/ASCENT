/* Main Include */
#include "Entities/Entity.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Entity::Entity(const sf::Vector2f position, const float speed)
    : Being()
    , m_position(position)
    , m_speed(speed)
    , m_velocity(sf::Vector2f(0.f, 0.f))
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

  void Entity::setSpeed(const float speed) {
    m_speed = speed;
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

  
  void Entity::setVelocity(const sf::Vector2f velocity) {
    m_velocity = velocity;
  }

  sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
  }

  void Entity::move() {
    m_velocity.y += Constants::GRAVITY * m_dt;
    
    if (m_velocity.y > Constants::MAX_FALL_SPEED)
      m_velocity.y = Constants::MAX_FALL_SPEED;

    m_sprite.move(m_velocity);

    if (m_velocity.x != 0 || m_velocity.y != 0)
      m_pCollisionManager->verifyCollision(this);
  }

  void Entity::move(const sf::Vector2f movement) {
    m_sprite.move(movement);
  }

  void Entity::collide(Entity* entity, CollisionType type, float overlap) {
    if (type == CollisionType::Horizontal) {
      entity->move(sf::Vector2f(overlap, 0));
    } else {
      entity->move(sf::Vector2f(0, overlap));
      entity->setVelocity(sf::Vector2f(0.f, 0.f));
    }
  }

  void Entity::setCollisionManager(Manager::CollisionManager* manager) {
    m_pCollisionManager = manager;
  }

  Manager::CollisionManager* Entity::m_pCollisionManager = NULL;
}