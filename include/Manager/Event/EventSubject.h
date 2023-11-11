#ifndef EVENTSUBJECT_H
#define EVENTSUBJECT_H

/* Program Defined */
#include "Manager/Event/EventObserver.h"

/* Standard Library */
#include <list>

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Manager {
  namespace Event {
    class EventSubject {
      protected:
        std::list<EventObserver*> m_observers;
        sf::Event m_event;

      public:
        EventSubject();
        virtual ~EventSubject();

        sf::Event getEvent() const;
        void setEvent(sf::Event event);

        virtual void attach(EventObserver*);
        virtual void detach(EventObserver*);
        virtual void notify();
    };
  };
}

#endif