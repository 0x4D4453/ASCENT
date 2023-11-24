#ifndef SPRING_H
#define SPRING_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Obstacles {
    class Spring : public Obstacle {
      enum SpringFrames {
        Contracted = 0,
        Normal,
        Extended,
        TotalFrames
      };

      private:
        sf::IntRect m_textureRect;
        const float m_strength;
        const float m_chargeTime;
        const float m_launchTime;
        float m_chargeTimeElapsed;
        float m_launchTimeElapsed;
        float m_animationTime;
        bool m_isCharging;
        bool m_isLaunching;
        int m_currentFrame;

      private:
        void checkCharge();
        void checkLaunch();
        void launch(Entity* pEntity);
        const float getLaunchAngle(sf::Vector2f position);

      public:
        Spring(
          Textures::ID textureID,
          sf::Texture& texture,
          sf::Vector2f position = sf::Vector2f(0.f, 0.f)
        );
        ~Spring();
        const bool getIsCharging() const;
        const bool getIsLaunching() const;
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void exec();
    };
  }
}

#endif 