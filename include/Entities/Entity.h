#ifndef ENTITY_H
#define ENTITY_H

/* Program Defined */
#include "Being.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities {
  class Entity : public Being {
    protected:
      sf::Vector2f m_position;
    
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
      Entity(sf::Vector2f position);
      virtual ~Entity();
      void setPosition(sf::Vector2f position);
      sf::Vector2f getPosition() const;
      Coordinates getCoordinates() const;
      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif