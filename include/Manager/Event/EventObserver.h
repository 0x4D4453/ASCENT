#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Manager {
  namespace Event {
    class EventSubject;

    class EventObserver {
      protected:
        EventSubject* m_pEventSubject;
        bool m_isActive;

      public:
        EventObserver(EventSubject* pEventSubject = NULL);
        virtual ~EventObserver();

        void setEventSubject(EventSubject* pEventSubject);

        virtual void keyPressed(const sf::Keyboard::Key key) = 0;
        virtual void keyReleased(const sf::Keyboard::Key key) = 0;
        virtual void lostFocus() = 0;
        virtual void textEntered(const char character) = 0;

        const bool getIsActive() const;
        void setIsActive(const bool isActive);
    };
  };
}

#endif