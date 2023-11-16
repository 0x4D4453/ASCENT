/* Main Include */
#include "Manager/Event/EventObserver.h"

/* Program Defined */
#include "Manager/Event/EventSubject.h"

namespace Manager {
  namespace Event {
    EventObserver::EventObserver(EventSubject* pEventSubject)
      : m_pEventSubject(pEventSubject)
      , m_isActive(true)
    {

    }

    EventObserver::~EventObserver() {
      m_pEventSubject->detach(this);
      m_pEventSubject = NULL;
    }

    void EventObserver::setEventSubject(EventSubject* pEventSubject) {
      m_pEventSubject = pEventSubject;
    }

    const bool EventObserver::getIsActive() const {
      return m_isActive;
    }

    void EventObserver::setIsActive(const bool isActive) {
      m_isActive = isActive;
    }
  };
}