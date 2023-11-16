/* Main Include */
#include "State/GameState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Context.h"

namespace States {
  GameState::GameState(const bool newGame)
    : State()
    , m_stageFactory(newGame, m_pContext->getMultiplayer())
  {
    setType(StateType::Game);
    m_pStage = m_stageFactory.createStage(m_pContext->getStage());

    if (!newGame)
      m_pStage->loadSaveGame();
  }

  GameState::~GameState() {
    delete m_pStage;
    m_pStage = NULL;
  }

  void GameState::keyPressed(sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::Escape):
        m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
        setPaused(true);
        break;
      default:
        break;
    }
  }

  void GameState::lostFocus() {
    m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
    setPaused(true);
  }

  void GameState::setPaused(const bool paused) {
    m_pStage->setPaused(paused);
  }

  void GameState::saveGame() {
    m_pStage->saveGame();
  }

  void GameState::exec() {
    m_pStage->exec();
  }
}