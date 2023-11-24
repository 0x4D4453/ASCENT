#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

/* Program Defined */
#include "Entities/Obstacles/Platform.h"

/* Forward Declaration */
#include "Entities/Characters/Player.h"

namespace Entities {
  namespace Obstacles {
    class MovingPlatform : public Platform {
      private:
        sf::Vector2f m_spawnPosition;
        const float m_range;
        bool m_direction;
      
      private:
        void movementPattern();

      public:
        MovingPlatform(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~MovingPlatform();
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
        virtual void exec();
    };
  }
}

#endif 