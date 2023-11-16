#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/Collision/CollisionStrategy.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <unordered_map>

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
      std::unordered_map<EntityTag, Manager::Collision::CollisionStrategy*> m_collisionStrategies;
      std::unordered_map<int, Entity*> m_collisionMap;
      EntityID m_entityId;
      EntityTag m_entityTag;
      EntityType m_entityType;
      sf::Vector2f m_position;
      sf::Vector2f m_velocity;
      float m_knockbackForce;
      float m_speed;
      bool m_isStaggered;
      bool m_moved;
    
    protected:
      void setEntityId(EntityID id);
      void setEntityTag(EntityTag tag);
      void setEntityType(EntityType group);
      void setSpeed(const float speed);
      void setKnockback(const float force);
      void setCollisionStrategy(EntityTag tag, Manager::Collision::StrategyId strategy);
      void move();
    
    public:
      Entity(const sf::Vector2f position, const float speed = 200.f);
      virtual ~Entity();

      static void setCollisionManager(Manager::Collision::CollisionManager* pManager);
      EntityID getEntityId() const;
      EntityTag getEntityTag() const;
      EntityType getEntityType() const;

      const float getKnockback() const;
      const bool getMoved() const;
      sf::Vector2f getPosition() const;
      void setPosition(sf::Vector2f position);
      sf::Vector2f getVelocity() const;
      void setVelocity(const sf::Vector2f velocity);
      void setIsStaggered(const bool isStaggered);
      const bool getIsStaggered() const;

      const bool getIsColliding() const;
      std::unordered_map<int, Entity*> getCollisionMap() const;
      Manager::Collision::CollisionStrategy* getCollisionStrategy(EntityTag tag) const;

      virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
      virtual void move(const sf::Vector2f movement);
      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif