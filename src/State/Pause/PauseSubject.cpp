/* Main Include */
#include "State/Pause/PauseSubject.h"

/* Program Defined */
#include <algorithm>

namespace States {
  namespace Pause {
    PauseSubject::PauseSubject()
      : m_isPaused(false)
    {

    }

    PauseSubject::~PauseSubject() {
      std::list<PauseObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        m_observers.remove(*it);
        it++;
      }
    }
    
    const bool PauseSubject::getIsPaused() const {
      return m_isPaused;
    }

    void PauseSubject::setIsPaused(const bool isPaused) {
      m_isPaused = isPaused;
    }
    
    void PauseSubject::attach(PauseObserver* o) {
      // Checks if element isn't already in the list
      if (std::find(m_observers.begin(), m_observers.end(), o) == m_observers.end())
        m_observers.push_back(o);
    }

    void PauseSubject::detach(PauseObserver* o) {
      m_observers.remove(o);
    }
    
    void PauseSubject::notifyPause() {
      std::list<PauseObserver*>::iterator it = m_observers.begin();

      while (it != m_observers.end()) {
        (*it)->updatePause();
        it++;
      }
    }
  };
}