/* Main Include */
#include "State/State.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/StateStack.h"
#include "Utility/Context.h"

namespace States {
  State::State()
    : Manager::Event::EventObserver(Manager::Event::EventManager::getInstance())
    , m_type(StateType::None)
    , m_pStateStack(States::StateStack::getInstance())
    , m_pGraphicsManager(Manager::GraphicsManager::getInstance())
    , m_pEventManager(Manager::Event::EventManager::getInstance())
    , m_pContext(Context::getInstance())
  {
    m_pEventManager->attach(this);
  }

  State::~State() {
    m_pEventManager->detach(this);
    m_pStateStack = NULL;
    m_pGraphicsManager = NULL;
    m_pEventManager = NULL;
  }

  const StateType State::getType() const {
    return m_type;
  }

  void State::setType(StateType type) {
    m_type = type;
  }

  void State::keyReleased(const sf::Keyboard::Key key) {

  }

  void State::lostFocus() {
    
  }

  void State::textEntered(const char character) {
    
  }
}