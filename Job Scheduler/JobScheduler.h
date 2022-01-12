#ifndef JobScheduler_H
#define JobScheduler_H

#include "Queue.h"
#include <pthread.h>

void *threadFunc(void *args);
class JobScheduler {
private:
  Queue *queue;
  long numThreads;
  char lastJobType;
  bool flag;
  pthread_t *threadIDs;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  pthread_mutex_t condMutex;
  pthread_barrier_t barrier;

public:
  JobScheduler(int numThreads);
  ~JobScheduler();
  // Getters
  Queue *getQueue() { return this->queue; };
  long getNumThreads() { return this->numThreads; };
  char getLastJobType() { return this->lastJobType; };
  bool getFlag() { return this->flag; };
  pthread_t *getThreadIDs() { return this->threadIDs; };
  pthread_mutex_t *getMutex() { return &(this->mutex); };
  pthread_cond_t *getCond() { return &(this->cond); };
  pthread_mutex_t *getCondMutex() { return &(this->condMutex); };
  pthread_barrier_t *getBarrier() { return &(this->barrier); };
  // Setters
  void setQueue(Queue *queue) { this->queue = queue; };
  void setNumThreads(long numThreads) { this->numThreads = numThreads; };
  void setLastJobType(char lastJobType) { this->lastJobType = lastJobType; };
  void setFlag(bool flag) { this->flag = flag; };
  void setThreadIDs(pthread_t *threadIDs) { this->threadIDs = threadIDs; };
  void setMutex(pthread_mutex_t mutex) { this->mutex = mutex; };
  void setCond(pthread_cond_t cond) { this->cond = cond; };
  void setCondMutex(pthread_mutex_t condMutex) { this->condMutex = condMutex; };
  void setBarrier(pthread_barrier_t barrier) { this->barrier = barrier; };
  // Utility
  void addJob(Job *job);
  Job *getJob();
  void decreaseRunningThreads();
  void increaseRunningThreads();
};

#endif