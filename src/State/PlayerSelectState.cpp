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
    : OptionsState(static_cast<int>(TotalOptions))
    , m_sprites()
  {
    setType(StateType::PlayerSelect);
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

    m_currentOption = static_cast<int>(OnePlayer);
    m_options[m_currentOption]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption].setColor(Constants::SELECTION_COLOR);
  }

  void PlayerSelectState::movePreviousOption() {
    if (m_currentOption - 1 < static_cast<int>(OnePlayer))
      return;

    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_sprites[m_currentOption].setColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption - 1]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption - 1].setColor(Constants::SELECTION_COLOR);

    m_currentOption = m_currentOption - 1;
  }

  void PlayerSelectState::moveNextOption() {
    if (m_currentOption + 1 >= static_cast<int>(TotalOptions))
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_sprites[m_currentOption].setColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption + 1]->setFillColor(Constants::SELECTION_COLOR);
    m_sprites[m_currentOption + 1].setColor(Constants::SELECTION_COLOR);

    m_currentOption = m_currentOption + 1;
  }

  void PlayerSelectState::changeState() {
    if (m_currentOption == TwoPlayer)
      m_pContext->setMultiplayer(true);
    else 
      m_pContext->setMultiplayer(false);

    m_pStateStack->pushState(StateType::StageSelect, NULL, true);
  }

  void PlayerSelectState::keyPressed(const sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::A): 
        movePreviousOption(); 
        break;
      case (sf::Keyboard::D): 
        moveNextOption(); 
        break;
      case (sf::Keyboard::Enter): 
        changeState(); 
        break;
      case (sf::Keyboard::Escape): 
        m_pStateStack->pushState(StateType::Menu, NULL, true); 
        break;
      default: break;
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