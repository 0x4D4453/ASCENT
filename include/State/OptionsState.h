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
      int m_currentOption;
      const int m_maxOption;
      sf::Sound m_optionSound;
   
    protected:
      virtual void createOption(const char* optionName, const sf::Vector2f& position);
      virtual void movePreviousOption();
      virtual void moveNextOption();
      virtual void setup() = 0;
      virtual void changeState() = 0;

    public:
      OptionsState(const int maxOption = 0);
      virtual ~OptionsState();
      virtual void keyPressed(const sf::Keyboard::Key key) = 0;
  };
}


#endif