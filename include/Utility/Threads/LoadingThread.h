#ifndef LOADINGTHREAD_H
#define LOADINGTHREAD_H

/* Program Defined */
#include "Utility/Threads/Thread.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Threads {
  class LoadingThread : public Thread {
    private:
      const bool m_newGame;
      States::GameState* m_pGameState;
    
    private:
      virtual void run();
    
    public:
      LoadingThread(const bool newGame = false, States::GameState* pGameState = NULL);
      ~LoadingThread();
      States::GameState* getGameState() const;
  };
}

#endif