#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

/* Program Defined */
#include "State/State.h"
#include "Utility/Threads/LoadingThread.h"

namespace States {
  class LoadingState : public State {
    private:
      Threads::LoadingThread m_thread;
      sf::Text m_loadingText;
    
    public:
      LoadingState(const bool newGame = true);
      ~LoadingState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      virtual void keyReleased(const sf::Keyboard::Key key);
      virtual void exec();
  };
}

#endif