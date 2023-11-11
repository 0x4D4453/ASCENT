/* Main Include */
#include "State/GameState.h"

/* Program Defined */
#include "State/StateStack.h"

namespace States {
  GameState::GameState(const bool newGame)
    : State()
    , m_stageFactory(newGame)
  {
    m_pStage = m_stageFactory.createStage("assets/stage_2.txt");

    if (!newGame)
      m_pStage->loadSaveGame();
  }

  GameState::~GameState() {
    delete m_pStage;
    m_pStage = NULL;
  }

  void GameState::handleKeyEvent(sf::Keyboard::Scancode keyScancode) {
    switch (keyScancode) {
      case (sf::Keyboard::Scancode::Escape):
        m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
        setPaused(true);
        break;
      default:
        break;
    }
  }

  void GameState::handleEvent(sf::Event& event) {
    switch (event.type) {
      case (sf::Event::KeyPressed): 
        handleKeyEvent(event.key.scancode); 
        break;
      case (sf::Event::LostFocus):
        m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
        setPaused(true);
        break;
      default:
        break;
    }
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