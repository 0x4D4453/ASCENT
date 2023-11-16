/* Main Include */
#include "State/Pause/PauseObserver.h"

/* Program Defined */
#include "State/Pause/PauseSubject.h"

namespace States {
  namespace Pause {
    PauseObserver::PauseObserver(PauseSubject* pPauseSubject)
      : m_pPauseSubject(pPauseSubject)
    {

    }

    PauseObserver::~PauseObserver() {
      m_pPauseSubject->detach(this);
      m_pPauseSubject = NULL;
    }

    void PauseObserver::setPauseSubject(PauseSubject* pPauseSubject) {
      m_pPauseSubject = pPauseSubject;
    }
  };
}