/* Main Include */
#include "Game.h"

/* Program Defined */
#include "Entities/Character.h"
#include "State/MenuState.h"

/* Standard Library */
#include <stdlib.h>
#include <time.h>

Game::Game() 
  : m_pGraphicsManager(Manager::GraphicsManager::getInstance())
  , m_pEventManager(Manager::Event::EventManager::getInstance())
  , m_pStateStack(States::StateStack::getInstance())
{
  srand(time(NULL));
  m_pStateStack->pushState(States::StateType::Menu);
  run();
}

Game::~Game() {
  delete m_pGraphicsManager;
  delete m_pEventManager;
  delete m_pStateStack;
}

void Game::run() {
  sf::Clock clock;

  while (m_pGraphicsManager->isOpen()) {
    m_pEventManager->pollEvents();
    m_pGraphicsManager->addTime(clock.restart());
    m_pGraphicsManager->clear();
    m_pStateStack->exec();
    m_pGraphicsManager->display();
  }
}