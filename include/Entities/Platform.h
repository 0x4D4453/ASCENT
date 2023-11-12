#ifndef PLATFORM_H
#define PLATFORM_H

/* Program Defined */
#include "Entities/Obstacle.h"

/* Forward Declaration */
namespace Entities { class Player; }

namespace Entities {
  class Platform : public Obstacle {
    private:
      void setup(const char* file);
      virtual void playerCollide(Player *player, CollisionType type);
    
    public:
      Platform(sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
      ~Platform();
      virtual void collide(Entity *entity, CollisionType type, float overlap);
      virtual void save();
      virtual void exec();
  };
}

#endif 