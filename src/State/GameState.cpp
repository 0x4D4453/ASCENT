/* Main Include */
#include "State/GameState.h"

/* Program Defined */
#include "State/StateStack.h"

namespace States {
  GameState::GameState()
    : State()
    , m_stage()
  {

  }

  GameState::~GameState() {

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
    m_stage.setPaused(paused);
  }

  void GameState::exec() {
    m_stage.exec();
  }
}