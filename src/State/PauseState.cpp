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
    : m_pGameState(pGameState)
    , m_background()
    , m_title("Pause", m_font)
    , m_currentOption(Continue)
  {
    setup();
  }

  PauseState::~PauseState() {

  }

  void PauseState::createOption(const char* optionName, const sf::Vector2f& position) {
    constexpr float characterSize = 80.f;

    sf::Text* pText = new sf::Text(optionName, m_font);

    if (!pText) {
      std::cerr << "Error creating option " << optionName << "\n";
      return;
    }

    pText->setCharacterSize(characterSize);
    sf::FloatRect textRect = pText->getLocalBounds();
    pText->setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    pText->setPosition(position);

    m_options.push_back(pText);
  }

  void PauseState::setup() {
    m_background.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(0.f, 0.f, 0.f, 150.f)); 
    m_background.setPosition(m_pGraphicsManager->getViewCoordinates().x, m_pGraphicsManager->getViewCoordinates().y);

    if (!m_font.loadFromFile("assets/fonts/monogram.ttf")) {
      std::cerr << "Error loading pause font!\n";
      exit(1);
    }

    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();
    
    m_title.setCharacterSize(80.f);
    sf::FloatRect textRect = m_title.getLocalBounds();
    m_title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    m_title.setPosition(viewCenterPosition.x, viewCenterPosition.y - 250.f);

    createOption("Continue", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y - 100.f));
    createOption("Save", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y));
    createOption("Save & Quit", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 100.f));
    createOption("Menu", sf::Vector2f(viewCenterPosition.x, viewCenterPosition.y + 200.f));

    m_options[m_currentOption]->setFillColor(sf::Color::Magenta);
  }

  void PauseState::handleEvent(sf::Event& event) {
    using namespace sf;

    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.scancode) {
        case (Keyboard::Scancode::W): 
          moveOptionUp(); 
          break;
        case (Keyboard::Scancode::S): 
          moveOptionDown(); 
          break;
        case (Keyboard::Scancode::Enter): 
          changeState(); 
          break;
        case (Keyboard::Scancode::Escape): 
          m_pStateStack->popState();
          m_pGameState->setPaused(false); 
          break;
        default: break;
      }
    }
  }
  
  void PauseState::moveOptionDown() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_options[m_currentOption]->setFillColor(sf::Color::White);
    m_options[m_currentOption + 1]->setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
  }

  void PauseState::moveOptionUp() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(Continue))
      return;
    
    m_options[m_currentOption]->setFillColor(sf::Color::White);
    m_options[m_currentOption - 1]->setFillColor(sf::Color::Magenta);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
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
      m_pGraphicsManager->getWindow()->draw(*(*it));
      ++it;
    }
  }
}