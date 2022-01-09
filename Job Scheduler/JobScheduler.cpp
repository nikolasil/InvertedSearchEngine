#include "JobScheduler.h"
#include "Queue.h"
#include "pthread.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void *threadFunc(void *args) {
  JobScheduler *scheduler = (JobScheduler *)args;
  cout << "thread  started" << endl;
  sleep(1);
  cout << "go to take job" << endl;
  scheduler->getJob()->execute();
  sleep(1);
  cout << "thread  ended" << endl;
}

JobScheduler::JobScheduler(int numThreads) {
  queue = new Queue();
  this->numThreads = numThreads;
  this->threadIDs = new pthread_t[numThreads];

  pthread_mutex_init(&(this->mutex), NULL);

  for (int i = 0; i < this->numThreads; i++) {
    int *t_id = new int();
    *t_id = i;
    // cout << "creating thread " << i << " " << *t_id << endl;
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
  Job *job = queue->remove()->getJob();
  pthread_mutex_unlock(&(this->mutex));
  return job;
}