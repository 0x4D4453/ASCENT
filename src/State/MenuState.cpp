/* Main Include */
#include "State/MenuState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"

/* Standard Library */
#include <iostream>

namespace States {
  MenuState::MenuState()
    : m_font()
    , m_options()
    , m_currentOption(NewGame)
  { 
    m_pGraphicsManager->resetView();
    setup();
  }

  MenuState::~MenuState() {

  }

  void MenuState::createOption(int index, const char* optionText, sf::Vector2f position) {
    if (index >= TotalOptions) {
      std::cerr << "Error adding option to menu!\n";
      return;
    }

    m_options.push_back(sf::Text(optionText, m_font));
    m_options[index].setFillColor(sf::Color::White);
    m_options[index].setCharacterSize(70);
    m_options[index].setPosition(position);
  }

  void MenuState::setup() {
    if (!m_font.loadFromFile("assets/fonts/monogram.ttf"))
      std::cerr << "Error loading Menu font!\n";
    
    createOption(0, "New Game", sf::Vector2f(50.f, 10.f));
    createOption(1, "Continue", sf::Vector2f(50.f, 100.f));
    createOption(2, "Highscore", sf::Vector2f(50.f, 190.f));
    createOption(3, "Credits", sf::Vector2f(50.f, 280.f));
    createOption(4, "Exit", sf::Vector2f(50.f, 360.f));

    m_options[m_currentOption].setFillColor(sf::Color::Magenta);
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
    
    m_options[m_currentOption].setFillColor(sf::Color::White);
    m_options[m_currentOption - 1].setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void MenuState::moveOptionDown() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_options[m_currentOption].setFillColor(sf::Color::White);
    m_options[m_currentOption + 1].setFillColor(sf::Color::Magenta);

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
        break;
      case Exit: 
        m_pGraphicsManager->close(); 
        break;
      default: break;
    }
  }

  void MenuState::exec() {
    std::vector<sf::Text>::iterator it = m_options.begin();
    
    while (it != m_options.end()) {
      m_pGraphicsManager->getWindow()->draw(*it);
      ++it;
    }
  }
}