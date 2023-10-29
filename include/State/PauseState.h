#ifndef PAUSESTATE_H
#define PAUSESTATE_H

/* Main Include */
#include "State/State.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>

/* Forward Declaration */
namespace States { class GameState; }

namespace States {
  class PauseState : public State, public sf::NonCopyable {
    private:
      enum Options {
        Continue,
        Menu,
        TotalOptions
      };

    private:
      States::GameState* m_pGameState;
      sf::RectangleShape m_background;
      sf::RectangleShape m_optionsBox;
      sf::Font m_font;
      sf::Text m_title;
      std::vector<sf::Text> m_options;
      Options m_currentOption;
    
    private:
      void moveOptionUp();
      void moveOptionDown();
      void changeState();
    
    public:
      PauseState(States::GameState* pGameState);
      ~PauseState();
      void handleEvent(sf::Event& event);
      void exec();
  };
}

#endif