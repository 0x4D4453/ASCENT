/* Main Include */
#include "Game.h"

/* Program Defined */
#include "Entities/Characters/Character.h"
#include "State/MenuState.h"

/* Standard Library */
#include <stdlib.h>
#include <time.h>

Game::Game() 
  : m_pGraphicsManager(Manager::GraphicsManager::getInstance())
  , m_pEventManager(Manager::Event::EventManager::getInstance())
  , m_pStateStack(States::StateStack::getInstance())
  , m_pContext(Context::getInstance())
{
  srand(time(NULL));
  m_pStateStack->pushState(States::StateType::Menu);
  run();
}

Game::~Game() {
  delete m_pGraphicsManager;
  delete m_pEventManager;
  delete m_pStateStack;
  delete m_pContext;
}

void Game::run() {
  while (m_pGraphicsManager->isOpen()) {
    m_pGraphicsManager->clear();
    m_pEventManager->pollEvents();
    m_pStateStack->exec();
    m_pGraphicsManager->display();
    m_pGraphicsManager->addTime();
  }
}