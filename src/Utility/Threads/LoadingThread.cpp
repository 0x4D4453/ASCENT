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
    m_pGameState = new States::GameState(m_newGame);

    if (!m_pGameState) {
      std::cerr << "Error creating Game State in thread!" << std::endl;
      exit(1);
    }

    sf::sleep(sf::Time(sf::seconds(0.2f)));

    m_finished = true;
    pthread_exit(NULL);
  }

  States::GameState* LoadingThread::getGameState() const {
    return m_pGameState;
  }
}