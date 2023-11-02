/* Main Include */
#include "State/OptionsState.h"

namespace States {
  OptionsState::OptionsState() 
    : m_options()
  {

  }

  OptionsState::~OptionsState() {
    std::vector<sf::Text*>::iterator it = m_options.begin();

    while (it != m_options.end()) {
      delete (*it);
      ++it;
    }
  }
}