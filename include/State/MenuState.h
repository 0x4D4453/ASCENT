#ifndef MENUSTATE_H
#define MENUSTATE_H

/* Main Include */
#include "State/OptionsState.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>

namespace States {
  class MenuState : public OptionsState, public sf::NonCopyable {
    private:
      enum Options {
        NewGame,
        Continue,
        Highscore,
        Credits,
        Exit,
        TotalOptions
      };

    private:
      Options m_currentOption;
    
    private:
      void createOption(const char* optionName, const sf::Vector2f& position);
      void setup();
      void moveOptionUp();
      void moveOptionDown();
      void changeState();
    
    public:
      MenuState();
      ~MenuState();
      void handleEvent(sf::Event& event);
      void exec();
  }; 
}

#endif //MENUSTATE_H