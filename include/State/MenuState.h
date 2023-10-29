#ifndef MENUSTATE_H
#define MENUSTATE_H

/* Main Include */
#include "State/State.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>

namespace States {
  class MenuState : public State, public sf::NonCopyable {
    private:
      enum Options {
        Play,
        Scoreboard,
        Credits,
        Exit,
        TotalOptions
      };

    private:
      sf::Font m_font;
      std::vector<sf::Text> m_text;
      Options m_currentOption;
    
    private:
      void createOption(int index, const char* optionText, sf::Vector2f position);
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