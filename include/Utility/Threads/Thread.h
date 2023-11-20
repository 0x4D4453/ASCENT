#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

namespace Threads {
  class Thread {
    protected:
      pthread_t m_threadID;
      pthread_attr_t m_tAttribute;
      bool m_finished;
    
    private:
      static void* runThread(void* pThread);
      virtual void run() = 0;

    public:
      Thread();
      virtual ~Thread();
      void start();
      void join();
      void yield(); 
      const bool getFinished() const;
  };
}

#endif