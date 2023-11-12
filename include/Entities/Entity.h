#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/Collision/CollisionStrategy.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  // Added E (from enum) to avoid type name errors
  enum EntityID {
    EntityE,
    CharacterE,
    ObstacleE,
    ProjectileE,
    EnemyE,
    PlayerE,
    PlatformE,
    GoombaE,
  };

  class Entity : public Being {
    protected:
      static Manager::Collision::CollisionManager* m_pCollisionManager;
      Manager::Collision::CollisionStrategy* m_pCollision;
      EntityID m_entityId;
      sf::Vector2f m_position;
      sf::Vector2f m_velocity;
      float m_speed;
      bool m_isStaggered;
    
    protected:
      void setEntityId(EntityID id);
      void setSpeed(const float speed);
    
    public:
      Entity(const sf::Vector2f position, const float speed = 200.f);
      virtual ~Entity();

      static void setCollisionManager(Manager::Collision::CollisionManager* manager);
      EntityID getEntityId() const;

      sf::Vector2f getPosition() const;
      void setPosition(sf::Vector2f position);
      sf::Vector2f getVelocity() const;
      void setVelocity(const sf::Vector2f velocity);
      void setIsStaggered(const bool isStaggered);
      const bool getIsStaggered() const;

      virtual void move();
      virtual void move(const sf::Vector2f movement);
      virtual void collide(Entity *entity, Manager::Collision::CollisionType type, float overlap);

      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif