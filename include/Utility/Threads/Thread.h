#ifndef THREAD_H
#define THREAD_H

/* Standard Library */
#include <pthread.h>

namespace Threads {
  // Código adapatado do Prof. Simão.
  // https://pessoal.dainf.ct.utfpr.edu.br/jeansimao/Fundamentos2/ThreadsPosix/Fundamentos2-ThreadsPThreadsPosix.htm
  class Thread {
    protected:
      pthread_t m_threadID;
      pthread_attr_t m_tAttribute;
      static pthread_mutex_t m_mutex;
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
      void lock();
      void unlock();
      void exitThread();
      const bool getFinished() const;
  };
}

#endif