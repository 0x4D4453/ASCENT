/* Main Include */
#include "State/StageSelectState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <iostream>

namespace States {
  StageSelectState::StageSelectState()
    : m_currentOption(Stage1)
  {
    setup();
  }

  StageSelectState::~StageSelectState() {

  }

  void StageSelectState::setup() {
    constexpr float distanceFromTop = Constants::WINDOW_HEIGHT/2.f - 100.f;

    createOption("Stage 1", sf::Vector2f(350.f, distanceFromTop));
    createOption("Stage 2", sf::Vector2f(Constants::WINDOW_WIDTH - 350.f, distanceFromTop));

    m_options[m_currentOption]->setFillColor(Constants::SELECTION_COLOR);
  }

  void StageSelectState::movePreviousOption() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(Stage1))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption - 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void StageSelectState::moveNextOption() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption + 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
  }

  void StageSelectState::changeState() {
    if (m_currentOption == Stage1)
      m_pContext->setStage(Constants::STAGE_1);
    else
      m_pContext->setStage(Constants::STAGE_3);

    m_pStateStack->pushState(StateType::Game, NULL, true);
  }

  void StageSelectState::handleEvent(sf::Event& event) {
    using namespace sf;

    if (event.type == Event::KeyPressed) {
      switch (event.key.scancode) {
        case (Keyboard::Scancode::A): 
          movePreviousOption(); 
          break;
        case (Keyboard::Scancode::D): 
          moveNextOption(); 
          break;
        case (Keyboard::Scancode::Enter): 
          changeState(); 
          break;
        case (Keyboard::Scancode::Escape): 
          m_pStateStack->pushState(StateType::PlayerSelect, NULL, true); 
        break;
        default: break;
      }
    }
  }

  void StageSelectState::exec() {
    std::vector<sf::Text*>::iterator it = m_options.begin();
    
    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }
  }
}