#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

/* Main Include */
#include "Manager/Event/EventSubject.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/Pause/PauseObserver.h"

/* SFML Library */
#include <SFML/System/NonCopyable.hpp>

namespace Manager {
  namespace Event {
    // Credits: Giovane Salvi for the base code and general idea
    class EventManager : public EventSubject, public States::Pause::PauseObserver, public sf::NonCopyable {
      private:
        static EventManager* m_instance;
        GraphicsManager *m_pGraphicsManager;
        bool m_isPaused;

      private:
        EventManager();
      
      public:
        ~EventManager();

        const bool getIsPaused() const;

        static EventManager* getInstance();
        void pollEvents();
        virtual void updatePause();
    };
  }
}

#endif