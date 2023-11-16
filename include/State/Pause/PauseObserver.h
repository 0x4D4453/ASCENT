#ifndef PAUSEOBSERVER_H
#define PAUSEOBSERVER_H

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace States {
  namespace Pause {
    class PauseSubject;

    class PauseObserver {
      protected:
        PauseSubject* m_pPauseSubject;

      public:
        PauseObserver(PauseSubject* pPauseSubject = NULL);
        virtual ~PauseObserver();

        void setPauseSubject(PauseSubject* pPauseSubject);

        virtual void updatePause() = 0;
    };
  };
}

#endif