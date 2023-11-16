#ifndef PAUSESUBJECT_H
#define PAUSESUBJECT_H

/* Program Defined */
#include "State/Pause/PauseObserver.h"

/* Standard Library */
#include <list>

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace States {
  namespace Pause {
    class PauseSubject {
      protected:
        std::list<PauseObserver*> m_observers;
        bool m_isPaused;

      public:
        PauseSubject();
        virtual ~PauseSubject();

        const bool getIsPaused() const;
        void setIsPaused(const bool isPaused);

        virtual void attach(PauseObserver*);
        virtual void detach(PauseObserver*);
        virtual void notifyPause();
    };
  };
}

#endif