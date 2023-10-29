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
      Entity(sf::Vector2f position);
      virtual ~Entity();
      void setPosition(sf::Vector2f position);
      sf::Vector2f getPosition() const;
      virtual void save() = 0;
      virtual void exec() = 0;
  };
};

#endif