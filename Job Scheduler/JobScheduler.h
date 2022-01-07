#ifndef JobScheduler_H
#define JobScheduler_H

#include "Queue.h"

class JobScheduler {
private:
  Queue *queue;
  int numJobs;
  int numProcesses;

public:
  JobScheduler(int numJobs, int numProcesses);
  ~JobScheduler();
};

#endif