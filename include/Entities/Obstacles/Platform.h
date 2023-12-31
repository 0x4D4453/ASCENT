#ifndef PLATFORM_H
#define PLATFORM_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

/* Forward Declaration */
namespace Entities { namespace Characters { class Player; } }

namespace Entities {
  namespace Obstacles {
    class Platform : public Obstacle {
      protected:
        const float m_bounciness;

      public:
        Platform(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~Platform();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void exec();
    };
  }
}

#endif 