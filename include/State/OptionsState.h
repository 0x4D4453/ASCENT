#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

/* Main Include */
#include "State/State.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <vector>

namespace States {
  class OptionsState : public State {
    protected:
      sf::Font m_font;
      std::vector<sf::Text*> m_options;
   
    protected:
      virtual void setup() = 0;
      virtual void moveOptionUp() = 0;
      virtual void moveOptionDown() = 0;
      virtual void changeState() =0;

    public:
      OptionsState();
      virtual ~OptionsState();
  };
}


#endif