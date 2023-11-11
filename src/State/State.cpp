/* Main Include */
#include "State/State.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/StateStack.h"

namespace States {
  State::State() 
    : m_pStateStack(States::StateStack::getInstance())
    , m_pGraphicsManager(Manager::GraphicsManager::getInstance())
    , m_pEventManager(Manager::Event::EventManager::getInstance())
  {
    m_pEventManager->attach(this);
  }

  State::~State() {
    m_pStateStack = NULL;
    m_pGraphicsManager = NULL;
    m_pEventManager->detach(this);
  }

  void State::eventUpdate(Manager::Event::EventSubject* subject) {
    if (subject != m_pEventManager)
      return;

    sf::Event event = m_pEventManager->getEvent();
    handleEvent(event);
  }
}