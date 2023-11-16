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
#include <iostream>

namespace States {
  PauseState::PauseState(States::GameState* pGameState) 
    : m_pGameState(pGameState)
    , m_background()
    , m_title("Pause", m_pContext->getFont(Fonts::Monogram))
    , m_currentOption(Continue)
  {
    setType(StateType::Pause);
    setup();
  }

  PauseState::~PauseState() {
  
  }

  void PauseState::setup() {
    m_background.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(0.f, 0.f, 0.f, 150.f)); 
    m_background.setPosition(m_pGraphicsManager->getViewCoordinates().x, m_pGraphicsManager->getViewCoordinates().y);

    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();
    
    m_title.setCharacterSize(80.f);
    sf::FloatRect textRect = m_title.getLocalBounds();
    m_title.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top + textRect.height/2.0f));
    m_title.setPosition(static_cast<int>(viewCenterPosition.x), static_cast<int>(viewCenterPosition.y - 250.f));

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

  void PauseState::movePreviousOption() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(Continue))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption - 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }
  
  void PauseState::moveNextOption() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption + 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
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

  void PauseState::exec() {
    m_pGraphicsManager->getWindow()->draw(m_background);
    m_pGraphicsManager->getWindow()->draw(m_title);

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