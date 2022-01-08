#ifndef JobScheduler_H
#define JobScheduler_H

#include "Queue.h"
#include <pthread.h>

void *threadFunc(void *args);
class JobScheduler {
private:
  Queue *queue;
  int numThreads;
  pthread_t *threadIDs;
  pthread_mutex_t mutex;

public:
  JobScheduler(int numThreads);
  ~JobScheduler();
  void addJob(Job *job);
};

#endif