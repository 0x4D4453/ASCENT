/* Main Include */
#include "State/OptionsState.h"

/* Program Defined */
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Sounds.h"

namespace States {
  OptionsState::OptionsState(const int maxOption) 
    : m_options()
    , m_currentOption(0)
    , m_maxOption(maxOption)
  {
    m_optionSound.setBuffer(m_pContext->getSound(Sounds::menuSound));
    m_optionSound.setVolume(10);
  }

  OptionsState::~OptionsState() {
    std::vector<sf::Text*>::iterator it = m_options.begin();

    while (it != m_options.end()) {
      delete (*it);
      ++it;
    }
  }

  void OptionsState::createOption(const char* optionName, const sf::Vector2f& position) {
    constexpr float characterSize = 80.f;

    sf::Text* pText = new sf::Text(optionName, m_pContext->getFont(Fonts::Monogram));

    if (!pText) {
      std::cerr << "Error creating option " << optionName << "\n";
      exit(1);
    }

    pText->setFillColor(Constants::DEFAULT_COLOR);
    pText->setOutlineColor(sf::Color::Black);
    pText->setOutlineThickness(2.f);
    pText->setCharacterSize(characterSize);
    centerTextOrigin(*pText);
    pText->setPosition(position);
    m_options.push_back(pText);
  }

  void OptionsState::movePreviousOption() {
    if (static_cast<int>(m_currentOption - 1) < 0)
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption - 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = m_currentOption - 1;
  }
  
  void OptionsState::moveNextOption() {
    if (static_cast<int>(m_currentOption + 1) >= m_maxOption)
      return;
    
    m_optionSound.play();
    m_options[m_currentOption]->setFillColor(Constants::DEFAULT_COLOR);
    m_options[m_currentOption + 1]->setFillColor(Constants::SELECTION_COLOR);

    m_currentOption = m_currentOption + 1;
  }
}