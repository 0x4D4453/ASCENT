/* Main Include */
#include "State/PauseState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

namespace States {
  PauseState::PauseState(States::GameState* pGameState) 
    : InStageState(static_cast<int>(TotalOptions), pGameState, "Pause")
  {
    setType(StateType::Pause);
    setup();
  }

  PauseState::~PauseState() {
  
  }

  void PauseState::setup() {
    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();
    
    createOption("Continue", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y - 100.f));
    createOption("Save", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y));
    createOption("Save & Quit", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 100.f));
    createOption("Menu", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 200.f));

    m_options[m_currentOption]->setFillColor(Constants::SELECTION_COLOR);
  }

  void PauseState::keyPressed(const sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::W):
        movePreviousOption();
        break;
      case (sf::Keyboard::S):
        moveNextOption();
        break;
      case (sf::Keyboard::Enter):
        changeState();
        break;
      case (sf::Keyboard::Escape):
        m_pStateStack->popState();
        m_pGameState->setPaused(false);
        break;
      default: break;
    }
  }

  void PauseState::changeState() {
    switch (m_currentOption) {
      case Continue: 
        m_pStateStack->popState();
        m_pGameState->setPaused(false);
        break;
      case Save:
        m_pGameState->saveGame();
      break;
      case SaveAndQuit:
        m_pGameState->saveGame();
        m_pStateStack->pushState(StateType::Menu, this, true);
      break;
      case Menu:
        m_pStateStack->pushState(StateType::Menu, NULL, true);
        break;
      default: break;
    }
  }
}