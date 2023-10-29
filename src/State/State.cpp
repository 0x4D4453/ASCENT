/* Main Include */
#include "State/State.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/StateStack.h"

namespace States {
  State::State() 
    : m_pStateStack(States::StateStack::getInstance())
    , m_pGraphicsManager(Manager::GraphicsManager::getInstance())
  {

  }

  State::~State() {
    m_pStateStack = NULL;
    m_pGraphicsManager = NULL;
  }
}