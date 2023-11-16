/* Main Include */
#include "Manager/InputManager.h"

/* Program Defined */
#include "Manager/Event/EventObserver.h"
#include "Utility/List.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Manager {
  InputManager* InputManager::m_instance(NULL);

  InputManager::InputManager()
    : EventObserver(Manager::Event::EventManager::getInstance())
    , m_pEventManager(Manager::Event::EventManager::getInstance())
    , m_pGraphicsManager(Manager::GraphicsManager::getInstance())
    , m_pPlayers(NULL)
  {
    m_pEventManager->attach(this);

    m_pressBinding.insert(std::make_pair(Entities::Player::MoveLeft, &Entities::Player::moveLeft));
    m_pressBinding.insert(std::make_pair(Entities::Player::MoveRight, &Entities::Player::moveRight));
    m_pressBinding.insert(std::make_pair(Entities::Player::Jump, &Entities::Player::chargeJump));

    m_releaseBinding.insert(std::make_pair(Entities::Player::MoveLeft, &Entities::Player::moveRight));
    m_releaseBinding.insert(std::make_pair(Entities::Player::MoveRight, &Entities::Player::moveLeft));
    m_releaseBinding.insert(std::make_pair(Entities::Player::Jump, &Entities::Player::jump));
  }

  InputManager::~InputManager() {
    m_pEventManager = NULL;
    m_pGraphicsManager = NULL;
    m_pPlayers = NULL;
  }

  InputManager* InputManager::getInstance() {
    if (m_instance == NULL)
      m_instance = new InputManager;

    return m_instance;
  }

  void InputManager::keyPressed(sf::Keyboard::Key key) {
    if (!m_pEventManager->getIsPaused())
      handleInput(key, m_pressBinding);
  }

  void InputManager::keyReleased(sf::Keyboard::Key key) {
    if (!m_pEventManager->getIsPaused())
      handleInput(key, m_releaseBinding);
  }

  void InputManager::lostFocus() {

  }

  void InputManager::handleInput(sf::Keyboard::Key key, std::unordered_map<Entities::Player::Actions, PlayerFunction> binding) {
    using namespace Entities;

    List<Entity*>::Iterator it = m_pPlayers->first();
    Player* pPlayer;

    while (it != m_pPlayers->last()) {
      pPlayer = dynamic_cast<Player*>(*it);

      if (!pPlayer->getIsJumping() && !pPlayer->getIsStaggered()) {
        Entities::Player::Actions action = pPlayer->getKeyAction(key);
        PlayerFunction pFunction = binding[action];
        (pPlayer->*binding[action])();
      }

      ++it;
    }
  }

  void InputManager::setPlayersList(EntityList* playersList) {
    m_pPlayers = playersList;
  }
}