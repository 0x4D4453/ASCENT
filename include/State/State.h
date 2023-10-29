#ifndef STATE_H
#define STATE_H

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }
namespace States { class StateStack; }

namespace States {
  enum class StateType {
    Menu,
    Game,
    Pause,
    TotalStates
  };

  class State {
    protected:
      States::StateStack* m_pStateStack;
      Manager::GraphicsManager* m_pGraphicsManager;
    
    public:
      State();
      virtual ~State();
      virtual void handleEvent(sf::Event& event) = 0;
      virtual void exec() = 0;
  };
}

#endif