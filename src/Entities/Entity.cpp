/* Main Include */
#include "Entities/Entity.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Manager::Collision::CollisionManager* Entity::m_pCollisionManager = NULL;
  Manager::Collision::CollisionStrategyFactory* Entity::m_pCollisionFactory(Manager::Collision::CollisionStrategyFactory::getInstance());

  Entity::Entity(const sf::Vector2f position, const float speed)
    : Being()
    , m_entityId(EntityID::EntityE)
    , m_position(position)
    , m_speed(speed)
    , m_velocity(sf::Vector2f(0.f, 0.f))
    , m_isStaggered(false)
    , m_pCollision(m_pCollisionFactory->getCollisionStrategy(Manager::Collision::StrategyId::Default))
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

  void Entity::setEntityId(EntityID id) {
    m_entityId = id;
  }

  EntityID Entity::getEntityId() const {
    return m_entityId;
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

  void Entity::setIsStaggered(const bool isStaggered) {
    m_isStaggered= isStaggered;
  }

  const bool Entity::getIsStaggered() const {
    return m_isStaggered;
  }

  void Entity::move() {
    m_sprite.move(m_velocity);

    if (m_velocity.x != 0 || m_velocity.y != 0)
      m_pCollisionManager->verifyCollision(this);
  }

  void Entity::move(const sf::Vector2f movement) {
    m_sprite.move(movement);
  }

  void Entity::collide(Entity* entity, Manager::Collision::CollisionType type, float overlap) {
    m_pCollision->collide(this, entity, type, overlap);
  }

  void Entity::setCollisionManager(Manager::Collision::CollisionManager* manager) {
    m_pCollisionManager = manager;
  }
}