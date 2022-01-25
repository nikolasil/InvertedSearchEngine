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
    // cout << "wait" << endl;
    pthread_mutex_lock(scheduler->getMutex());

    if (scheduler->getWaitAllAndSignal()) {
      pthread_mutex_unlock(scheduler->getMutex());

      pthread_barrier_wait(scheduler->getBarrier());

      pthread_mutex_lock(scheduler->getMutex());
      if (scheduler->getWaitAllAndSignal()) {
        scheduler->setWaitAllAndSignal(false);
        pthread_cond_signal(scheduler->getCond());
      }
      pthread_mutex_unlock(scheduler->getMutex());

      pthread_barrier_wait(scheduler->getBarrierAfter());
      continue;
    } else if (scheduler->getWaitAll()) {
      pthread_mutex_unlock(scheduler->getMutex());

      pthread_barrier_wait(scheduler->getBarrier());

      pthread_mutex_lock(scheduler->getMutex());
      if (scheduler->getWaitAll()) {
        scheduler->setWaitAll(false);
      }
      pthread_mutex_unlock(scheduler->getMutex());

      pthread_barrier_wait(scheduler->getBarrierAfter());
      continue;
    }
    j = NULL;
    j = scheduler->getJob();
    pthread_mutex_unlock(scheduler->getMutex());
    if (j == NULL) {
      continue;
    }
    if (j->getType() == '.')
      return NULL;
    j->execute();
  }
}

JobScheduler::JobScheduler(int numThreads) {
  queue = new Queue();
  this->numThreads = numThreads;
  this->threadIDs = new pthread_t[numThreads];
  this->lastJobType = 't';
  this->waitAllAndSignal = false;
  this->waitAll = false;
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
  for (int i = 0; i < this->numThreads; i++) {
    pthread_join(this->threadIDs[i], nullptr);
  }
  delete queue;
  delete this->threadIDs;
}

void JobScheduler::addJob(Job *job) {
  pthread_mutex_lock(&(this->mutex));
  queue->add(job);
  pthread_mutex_unlock(&(this->mutex));
}

Job *JobScheduler::getJob() {
  QueueNode *qn = queue->remove();
  if (qn != NULL) {
    if (qn->getJob()->getType() != this->lastJobType) {
      if (this->lastJobType == 't') { // first job ever OR after match documents
        this->setLastJobType(qn->getJob()->getType());
      } else if (!qn->getJob()->getStatus() && qn->getJob()->getType() == 'w') { // no more match documents
        this->setLastJobType('t');
        this->setWaitAllAndSignal(true);
        return NULL;
      } else {
        this->setLastJobType(qn->getJob()->getType());
        this->setWaitAll(true);
        queue->addToHead(qn->getJob());
        return NULL;
      }
    }

    return qn->getJob();
  }
  return NULL;
}