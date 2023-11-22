#ifndef INSTAGESTATE_H
#define INSTAGESTATE_H

/* Program Defined */
#include "State/OptionsState.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace States {
  class InStageState : public OptionsState {
    protected:
      GameState* m_pGameState;
      sf::RectangleShape m_background;
      sf::Text m_title;
    
    private:
      virtual void setup();
      virtual void changeState() = 0;
    
    public:
      InStageState(const int maxOption, States::GameState* pGameState, const char* titleString = "TITLE");
      ~InStageState();
      virtual void keyPressed(const sf::Keyboard::Key key) = 0;
      virtual void exec();
  };
}


#endif