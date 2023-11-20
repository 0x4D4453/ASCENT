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
    None = -1,
    Menu,
    PlayerSelect,
    StageSelect,
    Loading,
    Game,
    Continue,
    Pause,
    Ranking,
    TotalStates
  };

  class State : public Manager::Event::EventObserver {
    protected:
      StateType m_type;
      States::StateStack* m_pStateStack;
      Manager::GraphicsManager* m_pGraphicsManager;
      Manager::Event::EventManager* m_pEventManager;
      Context* m_pContext;
    
    public:
      State();
      virtual ~State();

      const StateType getType() const;
      void setType(StateType type);

      virtual void keyPressed(const sf::Keyboard::Key key) = 0;
      virtual void keyReleased(const sf::Keyboard::Key key);
      virtual void lostFocus();
      virtual void exec() = 0;
  };
}

#endif