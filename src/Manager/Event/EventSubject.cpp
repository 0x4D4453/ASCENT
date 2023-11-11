/* Main Include */
#include "Manager/Event/EventSubject.h"

namespace Manager {
  namespace Event {
    EventSubject::EventSubject() {

    }

    EventSubject::~EventSubject() {
      std::list<EventObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        m_observers.remove(*it);
        it++;
      }
    }

    sf::Event EventSubject::getEvent() const {
      return m_event;
    }

    void EventSubject::setEvent(sf::Event event) {
      m_event = event;
    }
    
    void EventSubject::attach(EventObserver* o) {
      m_observers.push_back(o);
    }

    void EventSubject::detach(EventObserver* o) {
      m_observers.remove(o);
    }

    void EventSubject::notify() {
      std::list<EventObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        (*it)->eventUpdate(this);
        it++;
      }
    }
  };
}