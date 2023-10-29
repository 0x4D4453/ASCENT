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
    , m_text()
    , m_currentOption(Play)
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

    m_text.push_back(sf::Text(optionText, m_font));
    m_text[index].setFillColor(sf::Color::White);
    m_text[index].setCharacterSize(70);
    m_text[index].setPosition(position);
  }

  void MenuState::setup() {
    if (!m_font.loadFromFile("assets/fonts/monogram.ttf"))
      std::cerr << "Error loading Menu font!\n";
    
    createOption(0, "Play", sf::Vector2f(50.f, 10.f));
    createOption(1, "Scoreboard", sf::Vector2f(50.f, 100.f));
    createOption(2, "Credits", sf::Vector2f(50.f, 190.f));
    createOption(3, "Exit", sf::Vector2f(50.f, 280.f));

    m_text[m_currentOption].setFillColor(sf::Color::Magenta);
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
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(Play))
      return;
    
    m_text[m_currentOption].setFillColor(sf::Color::White);
    m_text[m_currentOption - 1].setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void MenuState::moveOptionDown() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_text[m_currentOption].setFillColor(sf::Color::White);
    m_text[m_currentOption + 1].setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
  }

  void MenuState::changeState() {
    switch (m_currentOption) {
      case Play: 
        m_pStateStack->pushState(StateType::Game, this, true); 
        break;
      case Scoreboard: 
        break;
      case Exit: 
        m_pGraphicsManager->close(); 
        break;
      default: break;
    }
  }

  void MenuState::exec() {
    std::vector<sf::Text>::iterator it = m_text.begin();
    
    while (it != m_text.end()) {
      m_pGraphicsManager->getWindow()->draw(*it);
      ++it;
    }
  }
}