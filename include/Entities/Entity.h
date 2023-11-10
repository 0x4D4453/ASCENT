#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"
#include "Manager/CollisionManager.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  class Entity : public Being {
    protected:
      sf::Vector2f m_position;
      float m_speed;
      sf::Vector2f m_velocity;
      static Manager::CollisionManager* m_pCollisionManager;
    
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
      Entity(const sf::Vector2f position, const float speed = 300.f);
      virtual ~Entity();
      static void setCollisionManager(Manager::CollisionManager* manager);

      void setPosition(sf::Vector2f position);
      sf::Vector2f getPosition() const;
      Coordinates getCoordinates() const;
      void setVelocity(const sf::Vector2f velocity);
      sf::Vector2f getVelocity() const;

      virtual void move();
      virtual void move(const sf::Vector2f movement);
      virtual void collide(Entity *entity, CollisionType type, float overlap);

      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif