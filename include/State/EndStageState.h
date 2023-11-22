#ifndef ENDSTAGESTATE_H
#define ENDSTAGESTATE_H

/* Program Defined */
#include "State/InStageState.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace States {
  class EndStageState : public InStageState {
    private:
      enum Options {
        Retry,
        SaveScore,
        Menu,
        TotalOptions
      };

    private:
      virtual void setup();
      virtual void changeState();
    
    public:
      EndStageState(GameState* pGameState);
      ~EndStageState();
      virtual void keyPressed(const sf::Keyboard::Key key);
  };
}

#endif