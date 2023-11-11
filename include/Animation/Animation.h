#ifndef ANIMATION_H
#define ANIMATION_H

/* Standard Library */
#include <vector>

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Entities { class Entity; }

namespace Animations {
  class Animation {
    protected:
      Entities::Entity* m_pEntity;
      std::vector<sf::Texture*> m_animationFrames;
      int m_currentFrame;
      float m_totalTime;
      float m_timePerFrame;
    
    public:
      Animation(Entities::Entity* pEntity = NULL, float timePerFrame = 0.1f);
      ~Animation();
      void includeFrame(sf::Texture* pFrame);
  };
}

#endif