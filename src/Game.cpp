/* Main Include */
#include "Game.h"

/* Program Defined */
#include "Entities/Character.h"
#include "Manager/GraphicsManager.h"
#include "State/MenuState.h"
#include "State/StateStack.h"

Game::Game() 
  : m_pGraphicsManager(Manager::GraphicsManager::getInstance())
  , m_pStateStack(States::StateStack::getInstance())
{
  m_pStateStack->pushState(States::StateType::Menu);
  run();
}

Game::~Game() {
  delete m_pGraphicsManager;
  delete m_pStateStack;
}

void Game::run() {
  sf::Clock clock;

  while (m_pGraphicsManager->isOpen()) {
    m_pGraphicsManager->addTime(clock.restart());
    m_pGraphicsManager->pollEvents();
    m_pGraphicsManager->clear();
    m_pStateStack->exec();
    m_pGraphicsManager->display();
  }
}