/* Main Include */
#include "State/OptionsState.h"

/* Program Defined */
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
}