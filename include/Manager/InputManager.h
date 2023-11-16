#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

/* Program Defined */
#include "Entities/Player.h"
#include "Entities/EntityList.h"
#include "Manager/Event/EventObserver.h"
#include "Manager/Event/EventManager.h"
#include "Manager/GraphicsManager.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <unordered_map>

namespace Manager {
  typedef void (Entities::Player::*PlayerFunction)();
  class InputManager : public Manager::Event::EventObserver, public sf::NonCopyable {
    private:
      static InputManager* m_instance;
      Manager::Event::EventManager* m_pEventManager;
      Manager::GraphicsManager* m_pGraphicsManager;
      EntityList* m_pPlayers;
      std::unordered_map<Entities::Player::Actions, PlayerFunction> m_pressBinding;
      std::unordered_map<Entities::Player::Actions, PlayerFunction> m_releaseBinding;
    
    private:
      InputManager();
      void handleInput(sf::Keyboard::Key key, std::unordered_map<Entities::Player::Actions, PlayerFunction> binding);
    
    public:
      ~InputManager();
      static InputManager* getInstance();

      void setPlayersList(EntityList* playersList);
      
      virtual void keyPressed(const sf::Keyboard::Key key);
      virtual void keyReleased(const sf::Keyboard::Key key);
      virtual void lostFocus();
  };
}

#endif