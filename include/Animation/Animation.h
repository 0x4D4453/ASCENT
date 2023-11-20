#ifndef ANIMATION_H
#define ANIMATION_H

/* Standard Library */
#include <vector>

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
namespace Entities { class Entity; }

namespace Animations {
  class Animation {
    protected:
      Entities::Entity* m_pEntity;
      sf::IntRect m_textureRect;
      int m_currentFrame;
      float m_totalTime;
      float m_timePerFrame;
    
    public:
      Animation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~Animation();
      virtual void update(const float deltaTime) = 0;
  };
}

#endif