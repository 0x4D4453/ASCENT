/* Main Include */
#include "Manager/Event/EventSubject.h"

/* Program Defined */
#include <algorithm>

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
      // Checks if element isn't already in the list
      if (std::find(m_observers.begin(), m_observers.end(), o) == m_observers.end())
        m_observers.push_back(o);
    }

    void EventSubject::detach(EventObserver* o) {
      m_observers.remove(o);
    }
    
    void EventSubject::notifyKeyPressed(const sf::Keyboard::Key key) {
      std::list<EventObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        if ((*it)->getIsActive())
          (*it)->keyPressed(key);
        it++;
      }
    }

    void EventSubject::notifyKeyReleased(const sf::Keyboard::Key key) {
      std::list<EventObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        if ((*it)->getIsActive())
          (*it)->keyReleased(key);
        it++;
      }
    }

    void EventSubject::notifyLostFocus() {
      std::list<EventObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        if ((*it)->getIsActive())
          (*it)->lostFocus();
        it++;
      }
    }
  };
}