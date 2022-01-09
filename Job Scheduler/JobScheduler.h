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
  // Getters
  Queue *getQueue() { return this->queue; };
  int getNumThreads() { return this->numThreads; };
  pthread_t *getThreadIDs() { return this->threadIDs; };
  pthread_mutex_t getMutex() { return this->mutex; };
  // Setters
  void setQueue(Queue *queue) { this->queue = queue; };
  void setNumThreads(int numThreads) { this->numThreads = numThreads; };
  void setThreadIDs(pthread_t *threadIDs) { this->threadIDs = threadIDs; };
  void setMutex(pthread_mutex_t mutex) { this->mutex = mutex; };
  // Utility
  void addJob(Job *job);
  Job *getJob();
};

#endif