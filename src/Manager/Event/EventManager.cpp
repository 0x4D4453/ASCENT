/* Main Include */
#include "Manager/Event/EventManager.h"

namespace Manager {
  namespace Event {
    EventManager* EventManager::m_instance(NULL);

    EventManager::EventManager()
      : EventSubject()
      , m_pGraphicsManager(GraphicsManager::getInstance())
    {
      
    }
    
    EventManager::~EventManager() {
      m_pGraphicsManager = NULL;
    }

    EventManager* EventManager::getInstance() {
      if (!m_instance)
        m_instance = new EventManager();
      return m_instance;
    }

    void EventManager::pollEvents() {
      sf::RenderWindow* window = m_pGraphicsManager->getWindow();

      while (window->pollEvent(m_event))
          switch (m_event.type) {
            case sf::Event::Closed:
              window->close();
              break;
            default:
              notify();
              break;
          }
    }
  }
}