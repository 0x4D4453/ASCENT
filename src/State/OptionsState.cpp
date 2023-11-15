/* Main Include */
#include "State/OptionsState.h"

/* Program Defined */
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Sounds.h"

namespace States {
  OptionsState::OptionsState() 
    : m_options()
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
    pText->setCharacterSize(characterSize);
    sf::FloatRect textRect = pText->getLocalBounds();
    pText->setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top + textRect.height/2.0f));
    pText->setPosition(position);

    m_options.push_back(pText);
  }
}