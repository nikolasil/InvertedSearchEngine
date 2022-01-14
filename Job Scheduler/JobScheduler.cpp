#include "JobScheduler.h"
#include "Queue.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void *threadFunc(void *args) {
  JobScheduler *scheduler = (JobScheduler *)args;
  Job *j = NULL;
  while (1) {

    pthread_mutex_lock(scheduler->getMutex());

    if (scheduler->getQueue()->getLastJobType() != scheduler->getLastJobType()) {
      if (scheduler->getQueue()->getLastJobType() == 'w') {
        cout << "flag w" << endl;
        pthread_mutex_unlock(scheduler->getMutex());

        pthread_barrier_wait(scheduler->getBarrier());

        pthread_mutex_lock(scheduler->getMutex());
        pthread_cond_signal(scheduler->getCond());
        scheduler->setLastJobType('w');
        pthread_mutex_unlock(scheduler->getMutex());

        pthread_barrier_wait(scheduler->getBarrierAfter());

        pthread_mutex_lock(scheduler->getMutex());
      } else if (scheduler->getQueue()->getLastJobType() != 't') {
        cout << "flag" << endl;
        pthread_mutex_unlock(scheduler->getMutex());

        pthread_barrier_wait(scheduler->getBarrier());

        pthread_mutex_lock(scheduler->getMutex());
        // pthread_cond_signal(scheduler->getCond());
        scheduler->setLastJobType(scheduler->getQueue()->getLastJobType());
        pthread_mutex_unlock(scheduler->getMutex());

        pthread_barrier_wait(scheduler->getBarrierAfter());

        pthread_mutex_lock(scheduler->getMutex());
      }
    }

    j = NULL;
    j = scheduler->getJob();
    pthread_mutex_unlock(scheduler->getMutex());
    if (j == NULL) {
      continue;
    }
    if (j->getStatus()) {
      j->execute();
    }
  }
}

JobScheduler::JobScheduler(int numThreads) {
  queue = new Queue();
  this->numThreads = numThreads;
  this->threadIDs = new pthread_t[numThreads];
  this->lastJobType = 't';
  this->flag = false;
  pthread_mutex_init(&(this->mutex), NULL);
  pthread_mutex_init(&(this->condMutex), NULL);
  pthread_barrier_init(&(this->barrier), NULL, this->numThreads);
  pthread_barrier_init(&(this->barrierAfter), NULL, this->numThreads);
  pthread_cond_init(&(this->cond), NULL);

  for (int i = 0; i < this->numThreads; i++) {
    if (pthread_create(&this->threadIDs[i], nullptr, threadFunc, this) != 0) {
      perror("create thread");
      exit(-1);
    }
  }
}

JobScheduler::~JobScheduler() {
}

void JobScheduler::addJob(Job *job) {
  pthread_mutex_lock(&(this->mutex));
  queue->add(job);
  pthread_mutex_unlock(&(this->mutex));
}

Job *JobScheduler::getJob() {
  QueueNode *qn = queue->remove();
  if (qn != NULL) {
    if (this->getLastJobType() == 'w') {
      this->setLastJobType(qn->getJob()->getType());
      return NULL;
    }
    return qn->getJob();
  }
  return NULL;
}