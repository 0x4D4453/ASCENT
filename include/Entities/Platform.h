#ifndef PLATFORM_H
#define PLATFORM_H

/* Program Defined */
#include "Entities/Obstacle.h"

namespace Entities {
  class Platform : public Obstacle {
    private:
      void setup(const char* file);
    
    public:
      Platform(sf::Vector2f position = sf::Vector2f(0.f, 0.f), const char* file = "0");
      ~Platform();
      virtual void save();
      virtual void exec();
  };
}

#endif 