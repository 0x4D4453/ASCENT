/* Main Include */
#include "Utility/Threads/Thread.h"

/* Standard Library */
#include <iostream>
#include <pthread.h>

namespace Threads {
  Thread::Thread() 
    : m_threadID()
    , m_finished(false)
  {

  }

  Thread::~Thread() {

  }

  void Thread::start() {
    int status = pthread_attr_init(&m_tAttribute);
    status = pthread_attr_setscope(&m_tAttribute, PTHREAD_SCOPE_SYSTEM);

    if (status != 0)
      std::cerr << "Error initializing thread attribute!" << std::endl;

    status = pthread_create(&m_threadID, &m_tAttribute, Thread::runThread, static_cast<void*>(this));

    if (status != 0)
      std::cerr << "Error initializing thread!" << std::endl;

    status = pthread_attr_destroy(&m_tAttribute);
    
    if (status != 0)
      std::cerr << "Error destroying thread attribute!" << std::endl;
  }

  void Thread::join() {
    int status = pthread_join(m_threadID, NULL);
    if ( status != 0)
      std::cerr << "Join command failed!" << std::endl;
  }

  void* Thread::runThread(void* pThread) {
    Thread* sThread = static_cast<Thread*>(pThread);
    sThread->run();
    return NULL;
  }

  void Thread::yield() {
    sched_yield();
  }

  const bool Thread::getFinished() const {
    return m_finished;
  }
}