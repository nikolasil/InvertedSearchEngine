#include "JobScheduler.h"
#include "Queue.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void *threadFunc(void *args) {
  JobScheduler *scheduler = (JobScheduler *)args;
  Job *j;
  while (1) {
    j = scheduler->getJob();
    if (j != NULL) {
      j->print();
      j->execute();
      scheduler->decreaseRunningThreads();
    }
  }
}

JobScheduler::JobScheduler(int numThreads) {
  queue = new Queue();
  this->numThreads = numThreads;
  this->threadIDs = new pthread_t[numThreads];
  this->epoch = 0;
  this->currEpoch = 0;
  this->lastJobType = 's';
  this->runningThreads = 0;

  pthread_mutex_init(&(this->mutex), NULL);

  for (int i = 0; i < this->numThreads; i++) {
    if (pthread_create(&this->threadIDs[i], nullptr, threadFunc, this) != 0) {
      perror("create thread");
      exit(-1);
    }
  }
}

JobScheduler::~JobScheduler() {
}

void JobScheduler::decreaseRunningThreads() {
  pthread_mutex_lock(&(this->mutex));
  this->runningThreads--;
  pthread_mutex_unlock(&(this->mutex));
}

void JobScheduler::increaseRunningThreads() {
  pthread_mutex_lock(&(this->mutex));
  this->runningThreads++;
  pthread_mutex_unlock(&(this->mutex));
}

void JobScheduler::addJob(Job *job) {
  while (this->epoch - this->currEpoch > 1) {
  }
  pthread_mutex_lock(&(this->mutex));
  if (job->getType() != this->lastJobType) {
    this->epoch++;
    this->lastJobType = job->getType();
  }
  queue->add(job);
  job->setEpoch(this->epoch);
  pthread_mutex_unlock(&(this->mutex));
}

Job *JobScheduler::getJob() {

  if (this->queue->getSize() > 0) { // if there are jobs in the queue

    if (this->queue->getLastJobEpoch() == this->epoch) { // if the last job in the queue is of the same epoch
      pthread_mutex_lock(&(this->mutex));
      QueueNode *qn = queue->remove();
      if (qn != NULL) {
        runningThreads++;
        pthread_mutex_unlock(&(this->mutex));
        return qn->getJob();
      }

      pthread_mutex_unlock(&(this->mutex));

      return NULL;
    } else { // then the epoch must change when all the previous jobs are done
      while (runningThreads != 0) {
      }
      pthread_mutex_lock(&(this->mutex));
      cout << "waited to change epoch" << endl;
      currEpoch++;
      pthread_mutex_unlock(&(this->mutex));
    }
  }

  return NULL;
}