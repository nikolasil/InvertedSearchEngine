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
    if (scheduler->getFlag()) {
      cout << "flag " << scheduler->getLastJobType() << endl;
      pthread_barrier_wait(scheduler->getBarrier());
      pthread_mutex_lock(scheduler->getMutex());

      if (scheduler->getLastJobType() == 'm') {
        pthread_cond_signal(scheduler->getCond());
      }
      if (scheduler->getFlag()) {
        scheduler->setLastJobType(scheduler->getQueue()->getLastJobType());
        scheduler->setFlag(false);
      }
      pthread_mutex_unlock(scheduler->getMutex());
      pthread_barrier_wait(scheduler->getBarrier());
    }
    j = scheduler->getJob();
    if (j != NULL) {
      j->execute();
      // cout <<" executed" << endl;
    }
  }
}

JobScheduler::JobScheduler(int numThreads) {
  queue = new Queue();
  this->numThreads = numThreads;
  this->threadIDs = new pthread_t[numThreads];
  this->lastJobType = 's';
  this->flag = false;
  pthread_mutex_init(&(this->mutex), NULL);
  pthread_barrier_init(&(this->barrier), NULL, this->numThreads);
  pthread_cond_init(&(this->cond), NULL);
  pthread_mutex_init(&(this->condMutex), NULL);

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
  pthread_mutex_lock(&(this->mutex));
  if (flag) {
    pthread_mutex_unlock(&(this->mutex));
    return NULL;
  }
  // if the queue is empty
  if (this->queue->getSize() == 0) {
    if (this->getLastJobType() == 'm') {
      pthread_cond_signal(this->getCond());
    }
    pthread_mutex_unlock(&(this->mutex));
    return NULL;
  }
  // if the job type is different from the last job type
  if (this->queue->getLastJobType() != this->getLastJobType()) {
    // cout << "type " << this->queue->getLastJobType() << this->getLastJobType() << endl;
    this->flag = true;
    pthread_mutex_unlock(&(this->mutex));
    return NULL;
  }

  QueueNode *qn = queue->remove();
  if (qn != NULL) {
    qn->getJob()->print();
    pthread_mutex_unlock(&(this->mutex));
    return qn->getJob();
  }

  pthread_mutex_unlock(&(this->mutex));

  return NULL;
}