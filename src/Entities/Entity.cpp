/* Main Include */
#include "Entities/Entity.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Manager::Collision::CollisionManager* Entity::m_pCollisionManager = NULL;

  Entity::Entity(const sf::Vector2f position, const float scale, const float speed)
    : Being(scale)
    , m_entityId(EntityID::EntityE)
    , m_entityTag(EntityTag::ObstacleTag)
    , m_entityType(EntityType::Static)
    , m_position(position)
    , m_speed(speed)
    , m_knockbackForce(2.5f)
    , m_velocity(sf::Vector2f(0.f, 0.f))
    , m_isKnockbackResistant(false)
    , m_isStaggered(false)
    , m_moved(true)
  {
    setPosition(m_position);
  }

  Entity::~Entity() {
    m_collisionStrategies.clear();
    m_currentCollisions.clear();
  }
  
  void Entity::setEntityId(EntityID id) {
    m_entityId = id;
  }

  void Entity::setEntityTag(EntityTag tag) {
    m_entityTag = tag;
  }

  void Entity::setEntityType(EntityType group) {
    m_entityType = group;
  }

  EntityID Entity::getEntityId() const {
    return m_entityId;
  }

  EntityTag Entity::getEntityTag() const {
    return m_entityTag;
  }

  EntityType Entity::getEntityType() const {
    return m_entityType;
  }

  void Entity::setSpeed(const float speed) {
    m_speed = speed;
  }

  void Entity::setKnockback(const float force) {
    m_knockbackForce = force;
  }

  const float Entity::getKnockback() const {
    return m_knockbackForce;
  }

  const bool Entity::getMoved() const {
    return m_moved;
  }

  void Entity::setPosition(sf::Vector2f position) {
    m_position = position;
    m_sprite.setPosition(m_position);
  }

  sf::Vector2f Entity::getPosition() const {
    return m_sprite.getPosition();
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

  const bool Entity::getIsKnockbackResistant() const {
    return m_isKnockbackResistant;
  }

  const bool Entity::getIsColliding() const {
    return m_currentCollisions.size() > 0;
  }

  std::set<int>* Entity::getCurrentCollisions() {
    return &m_currentCollisions;
  }

  void Entity::move() {
    move(m_velocity);
  }

  void Entity::move(const sf::Vector2f movement) {
    m_moved = movement.x || movement.y;
    m_sprite.move(movement);
  }

  void Entity::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {

  }

  void Entity::setCollisionStrategy(EntityTag tag, Manager::Collision::StrategyId strategy) {
    Manager::Collision::CollisionStrategy* pStrategy = m_pCollisionManager->getCollisionStrategy(strategy);
    m_collisionStrategies[tag] = pStrategy;
  }

  Manager::Collision::CollisionStrategy* Entity::getCollisionStrategy(EntityTag tag) const {
    if (m_collisionStrategies.count(tag) == 0)
      return m_pCollisionManager->getCollisionStrategy(Manager::Collision::StrategyId::NoCollision);
      
    return m_collisionStrategies.at(tag);
  }

  void Entity::setCollisionManager(Manager::Collision::CollisionManager* pManager) {
    m_pCollisionManager = pManager;
  }
}