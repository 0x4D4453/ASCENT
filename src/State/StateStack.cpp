/* Main Include */
#include "State/StateStack.h"

/* Program Defined */
#include "State/State.h"
#include "State/GameState.h"
#include "State/LoadingState.h"
#include "State/MenuState.h"
#include "State/PauseState.h"
#include "State/PlayerSelectState.h"
#include "State/StageSelectState.h"
#include "State/EndStageState.h"
#include "State/SaveScoreState.h"
#include "State/RankingState.h"
#include "Utility/Context.h"

/* Standard Library */
#include <iostream>

namespace States {
  StateStack* StateStack::m_instance(NULL);

  StateStack::StateStack()
    : m_stack()
    , m_commandQueue()
    , m_pContext(Context::getInstance())
  {
    
  }

  void StateStack::createState(StateType stateType, State* pState) {
    State* state = NULL;

    switch (stateType) {
      case (StateType::Menu): 
        state = new MenuState; 
        break;
      case (StateType::PlayerSelect): 
        state = new PlayerSelectState; 
        break;
      case (StateType::StageSelect): 
        state = new StageSelectState; 
        break;
      case (StateType::Loading):
        state = new LoadingState;
        break;
      case (StateType::Game):
        state = pState;
        break;
      case (StateType::Continue):
        state = new LoadingState(false);
        break;
      case (StateType::Pause):
        state = new PauseState(static_cast<GameState*>(pState));
        break;
      case (StateType::EndStage):
        state = new EndStageState(static_cast<GameState*>(pState));
        break;
      case (StateType::SaveScore):
        state = new SaveScoreState;
        break;
      case (StateType::Ranking):
        state = new RankingState();
        break;
      default:
        break;
    }

    if (!state) {
      std::cerr << "Error creating " << static_cast<int>(stateType) << " state! \n";
      return;
    }

    if (m_stack.size() > 0)
      m_stack.back()->setIsActive(false);

    m_stack.push_back(state);
  }

  StateStack::~StateStack() {
    clearStates();
    delete m_pContext;
  }

  StateStack* StateStack::getInstance() {
    if (m_instance == NULL)
      m_instance = new StateStack;
    return m_instance;
  }

  void StateStack::pushState(StateType stateType, State* pState, const bool isReplacing) {
    Command command = Command::Push;

    if (isReplacing)
      command = Command::Clear;

    m_commandQueue.push(CommandDetails{command, stateType, pState});
  }

  void StateStack::popState() {
    m_commandQueue.push(CommandDetails{Command::Pop, StateType::TotalStates, NULL});
  }

  void StateStack::delayedPopState() {
    States::State* tmpState = m_stack.back();
    delete tmpState;
    m_stack.erase(m_stack.end() - 1);

    if (m_stack.size() > 0)
      m_stack.back()->setIsActive(true);
  }

  void StateStack::clearStates() {
    std::vector<State*>::iterator it = m_stack.begin();

    while (it != m_stack.end()) {
      delete *it;
      ++it;
    } 

    m_stack.clear(); 
  }

  void StateStack::applyPendingCommands() {
    while (!m_commandQueue.empty()) {
      CommandDetails cmd = m_commandQueue.front();

      switch (cmd.command) {
        case (Command::Push):
          createState(cmd.stateType, cmd.pState);
          break;
        case (Command::Pop):
          delayedPopState();
          break;
        case (Command::Clear):
          clearStates();
          createState(cmd.stateType, cmd.pState);
          break;
        default:
          break;
      }
      
      m_commandQueue.pop();
    }
  }

  State* StateStack::getBack() const {
    return m_stack.back();
  }

  void StateStack::exec() {
    applyPendingCommands();

    std::vector<State*>::iterator it = m_stack.begin();

    while (it != m_stack.end()) {
      (*it)->exec();
      ++it;
    }
  }

}