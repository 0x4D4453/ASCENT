/* Main Include */
#include "State/PauseState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <iostream>

namespace States {
  PauseState::PauseState(States::GameState* pGameState) 
    : m_background()
    , m_pGameState(pGameState)
    , m_currentOption(Continue)
  {
    m_background.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(0.f, 0.f, 0.f, 150.f)); 
    m_background.setPosition(m_pGraphicsManager->getViewCoordinates().x, m_pGraphicsManager->getViewCoordinates().y);

    if (!m_font.loadFromFile("assets/fonts/monogram.ttf"))
      std::cerr << "Error loading pause font!\n";
    
    m_title.setString("Pause");
    m_title.setFont(m_font);
    m_title.setCharacterSize(80.f);
    sf::FloatRect textRect = m_title.getLocalBounds();
    m_title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_title.setPosition(m_pGraphicsManager->getViewCenter().x, m_pGraphicsManager->getViewCenter().y - 250.f);

    m_options.push_back(sf::Text("Continue", m_font));
    m_options[0].setCharacterSize(80.f);
    textRect = m_options[0].getLocalBounds();
    m_options[0].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_options[0].setPosition(m_pGraphicsManager->getViewCenter().x, m_pGraphicsManager->getViewCenter().y - 100.f);

    m_options.push_back(sf::Text("Save", m_font));
    m_options[1].setCharacterSize(80.f);
    textRect = m_options[1].getLocalBounds();
    m_options[1].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_options[1].setPosition(m_pGraphicsManager->getViewCenter().x, m_pGraphicsManager->getViewCenter().y);

    m_options.push_back(sf::Text("Save & Quit", m_font));
    m_options[2].setCharacterSize(80.f);
    textRect = m_options[2].getLocalBounds();
    m_options[2].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_options[2].setPosition(m_pGraphicsManager->getViewCenter().x, m_pGraphicsManager->getViewCenter().y + 100.f);

    m_options.push_back(sf::Text("Menu", m_font));
    m_options[3].setCharacterSize(80.f);
    textRect = m_options[3].getLocalBounds();
    m_options[3].setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_options[3].setPosition(m_pGraphicsManager->getViewCenter().x, m_pGraphicsManager->getViewCenter().y + 200.f);

    m_options[m_currentOption].setFillColor(sf::Color::Magenta);
  }

  PauseState::~PauseState() {

  }

  void PauseState::handleEvent(sf::Event& event) {
    using namespace sf;

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.scancode) {
        case (Keyboard::Scancode::W): 
          this->moveOptionUp(); 
          break;
        case (Keyboard::Scancode::S): 
          this->moveOptionDown(); 
          break;
        case (Keyboard::Scancode::Enter): 
          this->changeState(); 
          break;
        case (Keyboard::Scancode::Escape): 
          m_pStateStack->popState();
          m_pGameState->setPaused(false); 
          break;
        default: break;
      }
    }
  }
  
  void PauseState::moveOptionUp() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(Continue))
      return;
    
    m_options[m_currentOption].setFillColor(sf::Color::White);
    m_options[m_currentOption - 1].setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void PauseState::moveOptionDown() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_options[m_currentOption].setFillColor(sf::Color::White);
    m_options[m_currentOption + 1].setFillColor(sf::Color::Magenta);

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

    std::vector<sf::Text>::iterator it = m_options.begin();

    while (it != m_options.end()) {
      m_pGraphicsManager->getWindow()->draw(*it);
      ++it;
    }
  }
}