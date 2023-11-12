#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/Collision/CollisionStrategy.h"
#include "Manager/Collision/CollisionStrategyFactory.h"

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
      static Manager::Collision::CollisionStrategyFactory* m_pCollisionFactory;
      EntityID m_entityId;
      sf::Vector2f m_position;
      sf::Vector2f m_velocity;
      float m_speed;
      bool m_isStaggered;
      Manager::Collision::CollisionStrategy* m_pCollision;
    
    protected:
      void setEntityId(EntityID id);
      void setSpeed(const float speed);
    
    public:
      class Coordinates {
        public:
          float left;
          float right;
          float top;
          float bottom;
        
        public:
          Coordinates(float l = 0.f, float r = 0.f, float t = 0.f, float b = 0.f);
          ~Coordinates();
      };
    
    public:
      Entity(const sf::Vector2f position, const float speed = 200.f);
      virtual ~Entity();

      static void setCollisionManager(Manager::Collision::CollisionManager* manager);
      EntityID getEntityId() const;

      sf::Vector2f getPosition() const;
      void setPosition(sf::Vector2f position);
      sf::Vector2f getVelocity() const;
      void setVelocity(const sf::Vector2f velocity);
      Coordinates getCoordinates() const;
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