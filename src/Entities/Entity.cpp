/* Main Include */
#include "Entities/Entity.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Manager::Collision::CollisionManager* Entity::m_pCollisionManager = NULL;

  Entity::Entity(const sf::Vector2f position, const float speed)
    : Being()
    , m_entityId(EntityID::EntityE)
    , m_entityTag(EntityTag::ObstacleTag)
    , m_entityType(EntityType::Static)
    , m_position(position)
    , m_speed(speed)
    , m_velocity(sf::Vector2f(0.f, 0.f))
    , m_isStaggered(false)
    , m_isColliding(true)
    , m_moved(true)
  {
    setPosition(m_position);
  }

  Entity::~Entity() {

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

  void Entity::setIsColliding(const bool isColliding) {
    m_isColliding= isColliding;
  }

  const bool Entity::getIsColliding() const {
    return m_isStaggered;
  }

  void Entity::move() {
    move(m_velocity);
  }

  void Entity::move(const sf::Vector2f movement) {
    m_moved = movement.x || movement.y;
    m_sprite.move(movement);
  }

  void Entity::collide(Entity *entity, Manager::Collision::CollisionType type, float overlap) {

  }

  void Entity::setCollisionStrategy(EntityTag tag, Manager::Collision::StrategyId strategy) {
    Manager::Collision::CollisionStrategy* pStrategy = m_pCollisionManager->getCollisionStrategy(strategy);

    std::map<EntityTag, Manager::Collision::CollisionStrategy*>::iterator it = m_collisionMap.find(tag);
    if (it == m_collisionMap.end())
      m_collisionMap.insert(std::make_pair(tag, pStrategy));
    else
      it->second = pStrategy;
  }

  Manager::Collision::CollisionStrategy* Entity::getCollisionStrategy(EntityTag tag) const {
    if (m_collisionMap.find(tag) == m_collisionMap.end())
      return m_pCollisionManager->getCollisionStrategy(Manager::Collision::StrategyId::NoCollision);
      
    return m_collisionMap.at(tag);
  }

  void Entity::setCollisionManager(Manager::Collision::CollisionManager* manager) {
    m_pCollisionManager = manager;
  }
}