/* Main Include */
#include "Utility/Threads/LoadingThread.h"

/* Program Defined */
#include "State/GameState.h"

namespace Threads {
  LoadingThread::LoadingThread(const bool newGame, States::GameState* pGameState)
    : Thread()
    , m_newGame(newGame)
    , m_pGameState(pGameState)
  {

  }

  LoadingThread::~LoadingThread() {

  }

  void LoadingThread::run() {
    lock();
    m_pGameState = new States::GameState(m_newGame);
    m_finished = true;
    unlock();
    exitThread();
  }

  States::GameState* LoadingThread::getGameState() const {
    return m_pGameState;
  }
}