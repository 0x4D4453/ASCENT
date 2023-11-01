#ifndef GAMESTATE_H
#define GAMESTATE_H

/* Main Include */
#include "State/State.h"

/* Program Defined */
#include "Stage/Stage.h"

/* SFML Library */
#include <SFML/System/NonCopyable.hpp>

namespace States {
  class GameState : public State, public sf::NonCopyable {
    private:
      Stages::Stage m_stage;

    private:
      void handleKeyEvent(sf::Keyboard::Scancode keyScancode);

    public:
      GameState(const bool newGame = true);
      ~GameState();
      void handleEvent(sf::Event& event);
      void setPaused(const bool paused);
      void saveGame();
      void exec();
  };
}

#endif