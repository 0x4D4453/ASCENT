/* Main Include */
#include "State/PauseState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <string>

namespace States {
  PauseState::PauseState(States::GameState* pGameState) 
    : InStageState(static_cast<int>(TotalOptions), pGameState, "Pause")
    , m_currentScore("Score: " + std::to_string(m_pContext->getScore()), m_pContext->getFont(Fonts::Monogram))
    , m_pauseSound(m_pContext->getSound(Sounds::Pause))
  {
    setType(StateType::Pause);
    setup();
    m_pauseSound.play();
  }

  PauseState::~PauseState() {
  
  }

  void PauseState::setup() {
    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();

    m_currentScore.setCharacterSize(80.f);
    m_currentScore.setOutlineColor(sf::Color::Black);
    m_currentScore.setOutlineThickness(2.f);
    centerTextOrigin(m_currentScore);
    m_currentScore.setPosition(sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y - 130.f));

    createOption("Continue", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y));
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
      case SaveAndQuit:
        m_pGameState->saveGame();
        m_pStateStack->pushState(StateType::Menu, NULL, true);
      break;
      case Menu:
        m_pStateStack->pushState(StateType::Menu, NULL, true);
        break;
      default: break;
    }
  }

  void PauseState::exec() {
    m_pGraphicsManager->resetView();
    m_pGraphicsManager->draw(m_background);
    m_pGraphicsManager->draw(m_title);
    m_pGraphicsManager->draw(m_currentScore);

    std::vector<sf::Text*>::iterator it = m_options.begin();
    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }

    sf::Time* timeSinceLastUpdate = m_pGraphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_pGraphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame)
      (*timeSinceLastUpdate) -= (*timePerFrame);
  }
}