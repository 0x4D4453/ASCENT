#ifndef EVENTOBSERVER_H
#define EVENTOBSERVER_H

namespace Manager {
  namespace Event {
    class EventSubject;

    class EventObserver {
      public:
        EventObserver();
        virtual ~EventObserver();
        virtual void eventUpdate(EventSubject* subject) = 0;
    };
  };
}

#endif