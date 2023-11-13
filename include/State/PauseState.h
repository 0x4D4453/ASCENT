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
      void handleEvent(sf::Event& event);
      void createOption(const char* optionName, const sf::Vector2f& position);
      void setup();
      void moveOptionUp();
      void moveOptionDown();
      void changeState();
    
    public:
      PauseState(States::GameState* pGameState);
      ~PauseState();
      void exec();
  };
}

#endif