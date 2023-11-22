/* Main Include */
#include "State/EndStageState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

namespace States {
  EndStageState::EndStageState(GameState* pGameState)
    : InStageState(static_cast<int>(TotalOptions), pGameState, "GAME OVER")
  {
    setType(StateType::EndStage);
    setup();
  }

  EndStageState::~EndStageState() {

  }

  void EndStageState::setup() {
    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();

    createOption("Retry", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y));
    createOption("Save Score", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 100));
    createOption("Menu", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 200));

    m_options[m_currentOption]->setFillColor(Constants::SELECTION_COLOR);
  }

  void EndStageState::keyPressed(const sf::Keyboard::Key key) {
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
      default: break;
    }
  }

  void EndStageState::changeState() {
    switch (m_currentOption) {
      case Retry:
        m_pStateStack->pushState(StateType::Loading, NULL, true);
        break;
      case SaveScore:
        m_pStateStack->pushState(StateType::SaveScore, NULL, true);
        break;
      case Menu:
        m_pStateStack->pushState(StateType::Menu, NULL, true);
        break;
      default: break;
    }
  }
}