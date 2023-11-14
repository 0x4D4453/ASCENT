/* Main Include */
#include "State/MenuState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <iostream>

namespace States {
  MenuState::MenuState()
    : m_currentOption(NewGame)
  { 
    m_pGraphicsManager->resetView();
    setup();
  }

  MenuState::~MenuState() {

  }

  void MenuState::createOption(const char* optionName, const sf::Vector2f& position) {
    constexpr float characterSize = 80.f;

    sf::Text* pText = new sf::Text(optionName, m_pContext->getFont(Fonts::Monogram));

    if (!pText) {
      std::cerr << "Error creating option " << optionName << "\n";
      return;
    }

    pText->setFillColor(sf::Color::White);
    pText->setCharacterSize(characterSize);
    pText->setPosition(position);

    m_options.push_back(pText);
  }

  void MenuState::setup() {
    createOption("New Game", sf::Vector2f(50.f, 10.f));
    createOption("Continue", sf::Vector2f(50.f, 100.f));
    createOption("Highscore", sf::Vector2f(50.f, 190.f));
    createOption("Credits", sf::Vector2f(50.f, 280.f));
    createOption("Exit", sf::Vector2f(50.f, 360.f));

    m_options[m_currentOption]->setFillColor(sf::Color::Magenta);
  }

  void MenuState::handleEvent(sf::Event& event) {
    using namespace sf;

    if (event.type == Event::KeyPressed) {
      switch (event.key.scancode) {
        case (Keyboard::Scancode::W): 
          this->moveOptionUp(); 
          break;
        case (Keyboard::Scancode::S): 
          this->moveOptionDown(); 
          break;
        case (Keyboard::Scancode::Enter): this->changeState(); 
          break;
        default: break;
      }
    }
  }

  void MenuState::moveOptionUp() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(NewGame))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(sf::Color::White);
    m_options[m_currentOption - 1]->setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void MenuState::moveOptionDown() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(sf::Color::White);
    m_options[m_currentOption + 1]->setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
  }

  void MenuState::changeState() {
    switch (m_currentOption) {
      case NewGame: 
        m_pStateStack->pushState(StateType::Game, this, true); 
        break;
      case Continue:
        m_pStateStack->pushState(StateType::Continue, this, true);
        break;
      case Highscore:
        m_pStateStack->pushState(StateType::Ranking, NULL, true);
        break;
      case Exit: 
        m_pGraphicsManager->close(); 
        break;
      default: break;
    }
  }

  void MenuState::exec() {
    std::vector<sf::Text*>::iterator it = m_options.begin();
    
    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }
  }
}