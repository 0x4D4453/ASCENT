#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

/* Main Include */
#include "Manager/Event/EventSubject.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"

/* SFML Library */
#include <SFML/System/NonCopyable.hpp>

namespace Manager {
  namespace Event {
    class EventManager : public EventSubject, public sf::NonCopyable {
      private:
        static EventManager* m_instance;
        GraphicsManager *m_pGraphicsManager;

      private:
        EventManager();
      
      public:
        ~EventManager();

        static EventManager* getInstance();
        void pollEvents();
    };
  }
}

#endif