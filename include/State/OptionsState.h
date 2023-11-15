#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

/* Main Include */
#include "State/State.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/* Standard Library */
#include <vector>

namespace States {
  class OptionsState : public State {
    protected:
      std::vector<sf::Text*> m_options;
      sf::Sound m_optionSound;
   
    protected:
      virtual void setup() = 0;
      virtual void movePreviousOption() = 0;
      virtual void moveNextOption() = 0;
      virtual void changeState() =0;

    public:
      OptionsState();
      virtual ~OptionsState();
  };
}


#endif