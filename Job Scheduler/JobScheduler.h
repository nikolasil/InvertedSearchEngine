#ifndef JobScheduler_H
#define JobScheduler_H

#include "Queue.h"
#include <pthread.h>

void *threadFunc(void *args);
class JobScheduler {
private:
  Queue *queue;
  long numThreads;
  long epoch;
  long currEpoch;
  char lastJobType;
  long runningThreads;
  pthread_t *threadIDs;
  pthread_mutex_t mutex;

public:
  JobScheduler(int numThreads);
  ~JobScheduler();
  // Getters
  Queue *getQueue() { return this->queue; };
  long getNumThreads() { return this->numThreads; };
  long getEpoch() { return this->epoch; };
  long getCurrEpoch() { return this->currEpoch; };
  char getLastJobType() { return this->lastJobType; };
  long getRunningThreads() { return this->runningThreads; };
  pthread_t *getThreadIDs() { return this->threadIDs; };
  pthread_mutex_t getMutex() { return this->mutex; };
  // Setters
  void setQueue(Queue *queue) { this->queue = queue; };
  void setNumThreads(long numThreads) { this->numThreads = numThreads; };
  void setEpoch(long epoch) { this->epoch = epoch; };
  void setCurrEpoch(long currEpoch) { this->currEpoch = currEpoch; };
  void setLastJobType(char lastJobType) { this->lastJobType = lastJobType; };
  void setRunningThreads(long runningThreads) { this->runningThreads = runningThreads; };
  void setThreadIDs(pthread_t *threadIDs) { this->threadIDs = threadIDs; };
  void setMutex(pthread_mutex_t mutex) { this->mutex = mutex; };
  // Utility
  void addJob(Job *job);
  Job *getJob();
  void decreaseRunningThreads();
  void increaseRunningThreads();
};

#endif