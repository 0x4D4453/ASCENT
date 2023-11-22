#ifndef GAMESTATE_H
#define GAMESTATE_H

/* Main Include */
#include "State/State.h"

/* Program Defined */
#include "Stage/Stage.h"
#include "Stage/StageFactory.h"

/* SFML Library */
#include <SFML/System/NonCopyable.hpp>

namespace States {
  class GameState : public State, public sf::NonCopyable {
    private:
      Stages::StageFactory m_stageFactory;
      Stages::Stage* m_pStage;

    public:
      GameState(const bool newGame = true);
      ~GameState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      virtual void lostFocus();
      void setPaused(const bool paused);
      void saveGame();
      void loadStageData();
      void gameOver();
      void exec();
  };
}

#endif