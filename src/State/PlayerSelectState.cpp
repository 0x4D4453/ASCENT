/* Main Include */
#include "State/PlayerSelectState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <iostream>

namespace States {
  PlayerSelectState::PlayerSelectState()
    : m_currentOption(OnePlayer)
    , m_sprites()
  {
    setup();
  }

  PlayerSelectState::~PlayerSelectState() {

  }
  
  void PlayerSelectState::setup() {
    constexpr float distanceFromTop = Constants::WINDOW_HEIGHT/2.f - 100.f;

    createOption("1 Player", sf::Vector2f(330.f, distanceFromTop));
    createOption("2 Players", sf::Vector2f(Constants::WINDOW_WIDTH - 350.f, distanceFromTop));

    m_sprites.push_back(sf::Sprite(m_pContext->getTexture(Textures::OnePlayer)));
    m_sprites.push_back(sf::Sprite(m_pContext->getTexture(Textures::TwoPlayers)));

    m_sprites[0].setOrigin(Constants::SPRITE_SIZE/2.f, 0);
    m_sprites[0].setScale(sf::Vector2f(Constants::SCALE * 4,  Constants::SCALE * 4));

    m_sprites[1].setOrigin(Constants::SPRITE_SIZE, 0);
    m_sprites[1].setScale(sf::Vector2f(Constants::SCALE * 4,  Constants::SCALE * 4));

    m_sprites[0].setPosition(330.f, distanceFromTop + 50.f);
    m_sprites[1].setPosition(Constants::WINDOW_WIDTH - 350.f, distanceFromTop + 50.f);

    m_options[m_currentOption]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption].setColor(Constants::SELECTION_COLOR);
  }

  void PlayerSelectState::movePreviousOption() {
    if (static_cast<int>(m_currentOption - 1) < static_cast<int>(OnePlayer))
      return;

    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_sprites[m_currentOption].setColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption - 1]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption - 1].setColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) - 1);
  }

  void PlayerSelectState::moveNextOption() {
    if (static_cast<int>(m_currentOption + 1) >= static_cast<int>(TotalOptions))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_sprites[m_currentOption].setColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption + 1]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption + 1].setColor(Constants::SELECTION_COLOR);

    m_currentOption = static_cast<Options>(static_cast<int>(m_currentOption) + 1);
  }

  void PlayerSelectState::changeState() {
    m_pStateStack->pushState(StateType::StageSelect, NULL, true);
  }

  void PlayerSelectState::handleEvent(sf::Event& event) {
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
          m_pStateStack->pushState(StateType::Menu, NULL, true); 
          break;
        default: break;
      }
    }
  }

  void PlayerSelectState::exec() {
    std::vector<sf::Text*>::iterator it = m_options.begin();
    
    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }

    for (int i = 0; i < m_sprites.size(); ++i)
      m_pGraphicsManager->draw(m_sprites[i]);
  }
}