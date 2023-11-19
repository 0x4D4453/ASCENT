/* Main Include */
#include "State/LoadingState.h"

/* Program Defined */
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Context.h"
#include "Utility/Constants.h"
#include "Utility/Fonts.h"
#include "Utility/Threads/LoadingThread.h"

/* Standard Library */
#include <iostream>

namespace States {
  LoadingState::LoadingState(const bool newGame) 
    : m_thread(newGame)
    , m_loadingText("Loading...", m_pContext->getFont(Fonts::Monogram))
  {
    m_loadingText.setFillColor(Constants::DEFAULT_COLOR);
    m_loadingText.setCharacterSize(80.f);
    m_loadingText.setPosition(Constants::WINDOW_WIDTH - 350.f, Constants::WINDOW_HEIGHT - 150.f);

    m_thread.start();
  }

  LoadingState::~LoadingState() {

  }

  void LoadingState::keyPressed(const sf::Keyboard::Key key) {

  }

  void LoadingState::keyReleased(const sf::Keyboard::Key key) {

  }

  void LoadingState::exec() {
    if (m_thread.getFinished())
      m_pStateStack->pushState(StateType::Game, static_cast<State*>(m_thread.getGameState()), true);
    
    m_pGraphicsManager->draw(m_loadingText);
  }
}