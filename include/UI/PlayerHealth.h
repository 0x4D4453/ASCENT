#ifndef PLAYERHEALTH_H
#define PLAYERHEALTH_H

/* Standard Library */
#include <vector>

/* SFML Library */
#include "SFML/Graphics.hpp"

/* Forward Declaration */
namespace Entities { namespace Characters { class Player; } }
namespace Manager { class GraphicsManager; }

namespace UI {
  class PlayerHealth {
    private:
      const int m_maxHearts;
      sf::Texture m_heartTexture;
      sf::IntRect m_textureRect;
      std::vector<sf::Sprite> m_heartContainer;
      const float m_timePerFrame;
      float m_totalTime;
      int m_currentFrame;

    public:
      PlayerHealth();
      ~PlayerHealth();
      void update(const float dt);
      void draw(Entities::Characters::Player* pPlayer, Manager::GraphicsManager* pGraphicsManager);
  };
}

#endif