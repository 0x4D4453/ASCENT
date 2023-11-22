#ifndef PAUSESTATE_H
#define PAUSESTATE_H

/* Main Include */
#include "State/InStageState.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>

/* Forward Declaration */
namespace States { class GameState; }

namespace States {
  class PauseState : public InStageState, public sf::NonCopyable {
    private:
      enum Options {
        Continue,
        Save,
        SaveAndQuit,
        Menu,
        TotalOptions
      };

    private:
      void setup();
      void changeState();
    
    public:
      PauseState(States::GameState* pGameState);
      ~PauseState();
      virtual void keyPressed(const sf::Keyboard::Key key);
  };
}

#endif