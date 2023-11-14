#ifndef STATE_H
#define STATE_H

/* Program Defined */
#include "Manager/Event/EventObserver.h"
#include "Manager/Event/EventManager.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
class Context;
namespace Manager { class GraphicsManager; }
namespace States { class StateStack; }

namespace States {
  enum class StateType {
    Menu,
    Game,
    Continue,
    Pause,
    Ranking,
    TotalStates
  };

  class State : public Manager::Event::EventObserver {
    protected:
      States::StateStack* m_pStateStack;
      Manager::GraphicsManager* m_pGraphicsManager;
      Manager::Event::EventManager* m_pEventManager;
      Context* m_pContext;

    protected:
      virtual void handleEvent(sf::Event& event) = 0;
    
    public:
      State();
      virtual ~State();
      virtual void eventUpdate(Manager::Event::EventSubject* subject);
      virtual void exec() = 0;
  };
}

#endif