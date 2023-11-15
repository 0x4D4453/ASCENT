#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/Collision/CollisionStrategy.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <map>

namespace Entities {
  // Added E (from enum) to avoid type name errors
  enum EntityID {
    EntityE = 0,
    CharacterE,
    ObstacleE,
    ProjectileE,
    EnemyE,
    PlayerE,
    PlatformE,
    GoombaE,
    FlyE,
  };

  enum EntityTag {
    ObstacleTag,
    PlayerTag,
    EnemyTag,
    ProjectileTag,
  };

  enum EntityType {
    Static,
    Dynamic,
  };

  class Entity : public Being {
    protected:
      static Manager::Collision::CollisionManager* m_pCollisionManager;
      std::map<EntityTag, Manager::Collision::CollisionStrategy*> m_collisionMap;
      EntityID m_entityId;
      EntityTag m_entityTag;
      EntityType m_entityType;
      sf::Vector2f m_position;
      sf::Vector2f m_velocity;
      float m_speed;
      bool m_isStaggered;
      bool m_isColliding;
    
    protected:
      void setEntityId(EntityID id);
      void setEntityTag(EntityTag tag);
      void setEntityType(EntityType group);
      void setSpeed(const float speed);
      void setCollisionStrategy(EntityTag tag, Manager::Collision::StrategyId strategy);
      void move();
    
    public:
      Entity(const sf::Vector2f position, const float speed = 200.f);
      virtual ~Entity();

      static void setCollisionManager(Manager::Collision::CollisionManager* manager);
      EntityID getEntityId() const;
      EntityTag getEntityTag() const;
      EntityType getEntityType() const;

      sf::Vector2f getPosition() const;
      void setPosition(sf::Vector2f position);
      sf::Vector2f getVelocity() const;
      void setVelocity(const sf::Vector2f velocity);
      void setIsStaggered(const bool isStaggered);
      const bool getIsStaggered() const;

      void setIsColliding(const bool isColliding);
      const bool getIsColliding() const;
      Manager::Collision::CollisionStrategy* getCollisionStrategy(EntityTag tag) const;

      virtual void collide(Entity *entity, Manager::Collision::CollisionType type, float overlap);
      virtual void move(const sf::Vector2f movement);
      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif