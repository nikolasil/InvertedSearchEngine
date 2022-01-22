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
  bool waitAllAndSignal;
  bool waitAll;
  pthread_t *threadIDs;
  pthread_mutex_t mutex;
  pthread_mutex_t condMutex;
  pthread_cond_t cond;
  pthread_barrier_t barrier;
  pthread_barrier_t barrierAfter;

public:
  JobScheduler(int numThreads);
  ~JobScheduler();
  // Getters
  Queue *getQueue() { return this->queue; };
  long getNumThreads() { return this->numThreads; };
  char getLastJobType() { return this->lastJobType; };
  bool getWaitAllAndSignal() { return this->waitAllAndSignal; };
  bool getWaitAll() { return this->waitAll; };
  pthread_t *getThreadIDs() { return this->threadIDs; };
  pthread_mutex_t *getMutex() { return &(this->mutex); };
  pthread_mutex_t *getCondMutex() { return &(this->condMutex); };
  pthread_cond_t *getCond() { return &(this->cond); };
  pthread_barrier_t *getBarrier() { return &(this->barrier); };
  pthread_barrier_t *getBarrierAfter() { return &(this->barrierAfter); };
  // Setters
  void setQueue(Queue *queue) { this->queue = queue; };
  void setNumThreads(long numThreads) { this->numThreads = numThreads; };
  void setLastJobType(char lastJobType) { this->lastJobType = lastJobType; };
  void setWaitAllAndSignal(bool waitAllAndSignal) { this->waitAllAndSignal = waitAllAndSignal; };
  void setWaitAll(bool waitAll) { this->waitAll = waitAll; };
  void setThreadIDs(pthread_t *threadIDs) { this->threadIDs = threadIDs; };
  void setMutex(pthread_mutex_t mutex) { this->mutex = mutex; };
  void setCondMutex(pthread_mutex_t condMutex) { this->condMutex = condMutex; };
  void setCond(pthread_cond_t cond) { this->cond = cond; };
  void setBarrier(pthread_barrier_t barrier) { this->barrier = barrier; };
  void setBarrierAfter(pthread_barrier_t barrierAfter) { this->barrierAfter = barrierAfter; };
  // Utility
  void addJob(Job *job);
  Job *getJob();
  void decreaseRunningThreads();
  void increaseRunningThreads();
};

#endif