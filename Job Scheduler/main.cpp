#include "Job.h"
#include "JobScheduler.h"
#include "Queue.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void func() {
  cout << "Job func" << endl;
}

int main() {
  JobScheduler *jobScheduler = new JobScheduler(5);

  jobScheduler->addJob(new Job('s', &func));
  jobScheduler->addJob(new Job('s', &func));
  sleep(2);
}
