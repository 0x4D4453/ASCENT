#ifndef PAUSESTATE_H
#define PAUSESTATE_H

/* Main Include */
#include "State/OptionsState.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>

/* Forward Declaration */
namespace States { class GameState; }

namespace States {
  class PauseState : public OptionsState, public sf::NonCopyable {
    private:
      enum Options {
        Continue,
        Save,
        SaveAndQuit,
        Menu,
        TotalOptions
      };

    private:
      States::GameState* m_pGameState;
      sf::RectangleShape m_background;
      sf::Text m_title;
      Options m_currentOption;
    
    private:
      void setup();
      void movePreviousOption();
      void moveNextOption();
      void changeState();
    
    public:
      PauseState(States::GameState* pGameState);
      ~PauseState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      void exec();
  };
}

#endif